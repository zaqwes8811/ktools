#include "rx_mem_pool.h"

#define LOG_NAME "[rx_mem_pool]"

static int rmp_deallocate(struct rx_mem_pool_t *self);

int rmp_init(struct rx_mem_pool_t *self, int max_cell_size,
	int cells_count, rx_mem_pool_cb proc_cb, void* user_data)
{
	int i;
	int ret;
	struct rx_mem_pool_cell_t *current_cell;

	VALIDATE_ARGPTR(self);

	self->cells_count = cells_count;
	self->cells = (struct rx_mem_pool_cell_t *) GENERAL_MALLOC(cells_count * sizeof(struct rx_mem_pool_cell_t));

	if (self->cells == NULL)
		return -ENOMEM;

	for (i = 0; i < self->cells_count; ++i) {
		current_cell = &self->cells[i];
		spin_lock_init(&current_cell->lock);
		INIT_WORK(&current_cell->proc_work, proc_cb);

		memset(&current_cell->buffer, 0, sizeof(current_cell->buffer));

		current_cell->buffer.addr = (unsigned char *) GENERAL_MALLOC(max_cell_size);
		if (current_cell->buffer.addr == NULL) {
			ret = -ENOMEM;
			goto free_allocated;
		}

		current_cell->buffer.max_size = max_cell_size;
		current_cell->buffer.cur_size = 0;

		current_cell->user_data = user_data;
		current_cell->index = i;

		current_cell->locked = false;
	}

	return 0;

free_allocated:
	(void) rmp_deallocate(self);
	return ret;
}

int rmp_deinit(struct rx_mem_pool_t *self)
{
	VALIDATE_ARGPTR(self);

	return rmp_deallocate(self);
}

int rmp_cancel_all_tasks(struct rx_mem_pool_t *self)
{
	int i;
	struct rx_mem_pool_cell_t *current_cell;

	VALIDATE_ARGPTR(self);

	for (i = 0; i < self->cells_count; ++i) {
		current_cell = &self->cells[i];
		(void) cancel_work_sync(&current_cell->proc_work);
	}

	return 0;
}

static int rmp_deallocate(struct rx_mem_pool_t *self)
{
	int i;
	struct rx_mem_pool_cell_t *current_cell;

	VALIDATE_ARGPTR(self);

	for (i = 0; i < self->cells_count; ++i) {
		current_cell = &self->cells[i];
		if (current_cell->buffer.addr != NULL) {
			(void) cancel_work_sync(&current_cell->proc_work);
			GENERAL_FREE(current_cell->buffer.addr);
		}
	}

	GENERAL_FREE(self->cells);
	return 0;
}

static int rmp_try_fill(struct rx_mem_pool_cell_t *self, bool *locked,
		const struct vector_const_view_u8_t buffer)
{
	VALIDATE_ARGPTR(self);
	VALIDATE_ARGPTR(locked);
	VALIDATE_ARGPTR(buffer.buffer);

	*locked = false;

	if (!self->locked) {
		self->buffer.cur_size = buffer.size;
		memcpy(self->buffer.addr, buffer.buffer, buffer.size);

		self->locked = true;
		*locked = true;
	}

	return 0;
}

static int rmp_release_cell(struct rx_mem_pool_cell_t *cell)
{
	VALIDATE_ARGPTR(cell);

	if (!cell->locked)
		return -EPROTO;

	cell->locked = false;
	return 0;
}

static int rmp_unload_and_release_cell_impl(struct rx_mem_pool_cell_t *self,
		struct vector_view_u8_t out_buffer, size_t *written)
{
	VALIDATE_ARGPTR(self);
	VALIDATE_ARGPTR(out_buffer.buffer);

	if (!self->locked) {
		pr_err("%s %s Cell already unlocked, idx: %d\n", LOG_NAME, __func__, self->index);
		return -EPROTO;
	}

	if (out_buffer.size < self->buffer.cur_size) {
		pr_err("%s %s Incorrect buffer size, idx: %d, got: %lu, expected at least: %u\n",
				LOG_NAME, __func__, self->index, out_buffer.size, self->buffer.cur_size);
		return -EINVAL;
	}

	*written = self->buffer.cur_size;

	memcpy(out_buffer.buffer, self->buffer.addr, self->buffer.cur_size);
	return rmp_release_cell(self);
}

/*
 * Concurency specific
 */
int rmp_try_claim_and_fill(
		struct rx_mem_pool_t *self, const unsigned char *data, size_t data_size, bool irqsave,
		struct rx_mem_pool_cell_t **cell)
{
	int ret;
	int i;
	struct rx_mem_pool_cell_t *current_cell;
	bool locked;
	unsigned long flags;

	VALIDATE_ARGPTR(self);
	VALIDATE_ARGPTR(data);
	VALIDATE_ARGPTR(cell);
	
	for (i = 0; i < self->cells_count; ++i) {
		current_cell = &self->cells[i];

		RETURN_IF(data_size > current_cell->buffer.max_size, -EINVAL,
				"%s %s input data size is too big, have: %d, got: %lu\n", LOG_NAME, __func__,
				current_cell->buffer.max_size, data_size);

		/* Ignore cells whitch are pending or execution now.
		 * It's pessimistic check and at lock time work may be reschedulable already
		 * It's not a problem. ISR path is serialized and queue execution to, but in general case
		 * work_busy/pending recommended not to use
		 */
		if (work_busy(&current_cell->proc_work)) {
			continue;
		}

		/* We have to take cell and fill it atomically */
		if (irqsave)
			spin_lock_irqsave(&current_cell->lock, flags);
		else
			spin_lock(&current_cell->lock);

		ret = rmp_try_fill(current_cell, &locked, CONST_VEC_VIEW_FROM(data, data_size));

		if (irqsave)
			spin_unlock_irqrestore(&current_cell->lock, flags);
		else
			spin_unlock(&current_cell->lock);

		RETURN_IF(ret < 0, ret, "%s %s Opration failed with ec: %d\n", LOG_NAME, __func__, ret);

		if (locked) {
			*cell = current_cell;
			return 0;
		}
	}

	pr_err("%s %s No free rx cells found\n", LOG_NAME, __func__);
	return -ENOMEM;
}

int rmp_release_by_idx(struct rx_mem_pool_t *self, size_t index, bool irqsave)
{
	int ret;
	unsigned long flags;
	struct rx_mem_pool_cell_t *current_cell;

	VALIDATE_ARGPTR(self);

	RETURN_IF(index >= self->cells_count, -EINVAL,
			"%s %s Out of bound with idx: %lu\n", LOG_NAME, __func__, index);

	current_cell = &self->cells[index];

	if (irqsave)
		spin_lock_irqsave(&current_cell->lock, flags);
	else
		spin_lock(&current_cell->lock);

	ret = rmp_release_cell(current_cell);
	if (irqsave)
		spin_unlock_irqrestore(&current_cell->lock, flags);
	else
		spin_unlock(&current_cell->lock);
	return ret;
}

int rmp_unload_and_release_cell(struct rx_mem_pool_cell_t *self,
		struct vector_view_u8_t out_buffer, bool irqsave, size_t *written)
{
	int ret;
	unsigned long flags;

	VALIDATE_ARGPTR(self);
	VALIDATE_ARGPTR(written);
	VALIDATE_ARGPTR(out_buffer.buffer);

	if (irqsave)
		spin_lock_irqsave(&self->lock, flags);
	else
		spin_lock(&self->lock);

	ret = rmp_unload_and_release_cell_impl(self, out_buffer, written);

	if (irqsave)
		spin_unlock_irqrestore(&self->lock, flags);
	else
		spin_unlock(&self->lock);

	return ret;
}

int rmp_unload_and_release_cell_by_index(struct rx_mem_pool_t *self,
		struct vector_view_u8_t out_buffer, bool irqsave, size_t *written, int index)
{
	VALIDATE_ARGPTR(self);

	RETURN_IF(index >= self->cells_count, -EINVAL,
			"%s %s Out of bound with idx: %d\n", LOG_NAME, __func__, index);

	return rmp_unload_and_release_cell(&self->cells[index], out_buffer, irqsave, written);
}
