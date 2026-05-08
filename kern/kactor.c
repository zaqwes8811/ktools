#include <soc/atom/kactor.h>
#include <soc/atom/sfi_sys_primitives.h>

#define LOG_NAME  "[kactor]"
#define KA_Q_NAME_MAX_SIZE  (32U)

static void ka_mem_pool_cb(struct work_struct *work_arg)
{
	int ret;
	const bool irqsave = false;  /* Not sharing pool with ISR */
	struct rx_mem_pool_cell_t *rx_mem_cell;
	struct kactor_work_t w;
	size_t written;

	VALIDATE_ARGPTR_WITH(work_arg, RET_VOID());

	rx_mem_cell = container_of(work_arg, struct rx_mem_pool_cell_t, proc_work);

	ret = rmp_unload_and_release_cell(rx_mem_cell, VEC_VIEW_FROM((uint8_t *) &w, sizeof(w)), irqsave, &written);
	RETURN_IF(ret < 0, RET_VOID(), "%s %s Can't unload cell [%d], ec: %d\n", LOG_NAME, __func__,
			rx_mem_cell->index, ret);
	RETURN_IF(written != sizeof(w), RET_VOID(),
			"%s %s Incorrect written size, got: %lu, expected: %lu\n", LOG_NAME, __func__,
			written, sizeof(w));

	if (w.cb != NULL)
		w.cb(w.arg);
}

int ka_init(struct kactor_t *self, size_t q_depth)
{
	int ret;
	char wq_name[KA_Q_NAME_MAX_SIZE];

	VALIDATE_ARGPTR(self);

	mutex_init(&self->lock);

	self->fillable = true;

	/* Queue name should be unique */
	memset(wq_name, 0x00, sizeof(wq_name));
	ret = snprintf(wq_name, sizeof(wq_name) - 1U, "actr_%p", (void *) self);
	RETURN_IF(ret < 0, ret, "%s %s Can't fill wq name for object: %p, ec: %d\n",
			LOG_NAME, __func__, (void *) self, ret);

	ret = rmp_init(&self->rx_mem_pool, sizeof(struct kactor_work_t), q_depth, ka_mem_pool_cb, self);
	RETURN_IF(ret < 0, ret,
			"%s %s Can't init work queue, ec: %d\n", LOG_NAME, __func__, ret);

	self->seq_q = create_singlethread_workqueue(wq_name);
	GOTO_IF_WITH_EC(self->seq_q == NULL, -ENODEV, deinit_rmp,
			"%s %s Can't init work queue for channel: %s\n", LOG_NAME, __func__, wq_name);
	return 0;
deinit_rmp:
	(void) rmp_deinit(&self->rx_mem_pool);
	return ret;
}

int ka_deinit(struct kactor_t *self)
{
	VALIDATE_ARGPTR(self);

	mutex_lock(&self->lock);

	self->fillable = false;
	rmp_cancel_all_tasks(&self->rx_mem_pool);
	flush_workqueue(self->seq_q);

	destroy_workqueue(self->seq_q);
	(void) rmp_deinit(&self->rx_mem_pool);

	mutex_unlock(&self->lock);
	return 0;
}

static int ka_push_impl(struct kactor_t *self, struct kactor_work_t w)
{
	int ret;
	bool scheduled;
	const bool irqsave = false;  /* Not sharing pool with ISR */
	struct rx_mem_pool_cell_t *cell;

	VALIDATE_ARGPTR(self);

	RETURN_IF(!self->fillable, -EINVAL, "%s %s Queue isn't fillable\n", LOG_NAME, __func__);

	ret = rmp_try_claim_and_fill(&self->rx_mem_pool, (const uint8_t *) &w, sizeof(w), irqsave, &cell);
	RETURN_IF(ret < 0, ret, "%s %s Can't claim and fill buffer, ec: %d\n", LOG_NAME, __func__, ret);

	scheduled = queue_work(self->seq_q, &cell->proc_work) != 0;
	if (!scheduled) {
		(void) rmp_release_by_idx(&self->rx_mem_pool, cell->index, irqsave);

		pr_err("%s %s Processing work already in work queue\n", LOG_NAME, __func__);
		return -EPROTO;
	}
	return 0;
}

int ka_push(struct kactor_t *self, struct kactor_work_t w)
{
	int ret;

	VALIDATE_ARGPTR(self);

	mutex_lock(&self->lock);
	ret = ka_push_impl(self, w);
	mutex_unlock(&self->lock);

	RETURN_IF(ret < 0, ret, "%s %s Can't claim and fill buffer, ec: %d\n", LOG_NAME, __func__, ret);
	return 0;
}
