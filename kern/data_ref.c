#include "data_ref.h"

#include <soc/atom/sfi_sys_primitives.h>

#define DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS  (1000)
#define LOG_NAME  "[data_ref]"

void drf_work_handler(struct work_struct *work)
{
	struct data_ref_t *ref = container_of(work, struct data_ref_t, work);

	if (ref->release_detached && ref->obj_detached) {
		ref->release_detached(ref->obj_detached);
		kfree(ref->obj_detached);
	}

	complete(&ref->released);
}

int drf_assign_once(struct data_ref_t *dref, void *user_data,
		data_ref_release_callback_t user_release)
{
	struct data_refcount_t *obj;

	VALIDATE_ARGPTR(dref);
	VALIDATE_ARGPTR(user_data);

	/* No allocation or deallocation under lock */
	obj = kmalloc(sizeof(*obj), GFP_KERNEL);
	RETURN_IF(obj == NULL, -ENOMEM, "%s %s Can't allocate memory for object\n",
			LOG_NAME, __func__);

	obj->release = user_release;
	obj->user_data = user_data;
	refcount_set(&obj->refcnt, 1);  /* Start with one claim */

	spin_lock(&dref->lock);
	if (dref->obj != NULL) {
		spin_unlock(&dref->lock);
		kfree(obj);

		pr_err("%s %s Object already initialized\n", LOG_NAME, __func__);
		return -EBUSY;
	}
	dref->obj = obj;
	spin_unlock(&dref->lock);
	return 0;
}

void *drf_acquire(struct data_ref_t *dref)
{
	struct data_refcount_t *obj;
	void *result = NULL;

	VALIDATE_ARGPTR_WITH(dref, NULL);

	spin_lock(&dref->lock);
	obj = dref->obj;
	if (obj && refcount_inc_not_zero(&obj->refcnt)) {
		result = obj->user_data;
	}
	spin_unlock(&dref->lock);
	return result;
}

int drf_put(struct data_ref_t *dref)
{
	data_ref_release_callback_t release = NULL;
	struct data_refcount_t *obj;

	VALIDATE_ARGPTR(dref);

	spin_lock(&dref->lock);
	obj = dref->obj;
	if (!obj) {
		spin_unlock(&dref->lock);
		return -EINVAL;
	}

	if (refcount_dec_and_test(&obj->refcnt)) {
		if (obj->release) {
			release = obj->release;
			obj->release = NULL;
			dref->obj = NULL;
		}
	}
	spin_unlock(&dref->lock);

	if (release) {
		dref->obj_detached = obj;
		dref->release_detached = release;

		schedule_work(&dref->work);  /* Destroy out of potential atomic context */
	}
	return 0;
}

int drf_destroy(struct data_ref_t *dref)
{
	int ret;
	const unsigned long timeout = msecs_to_jiffies(DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS);

	VALIDATE_ARGPTR(dref);

	drf_put(dref);  /* Match start claim */

	ret = wait_for_completion_interruptible_timeout(&dref->released, timeout);

	cancel_work_sync(&dref->work);  /* Wait for work fully finished */

	RETURN_IF(ret == 0, -ETIMEDOUT, "%s %s Operation timed out after %d ms\n",
			LOG_NAME, __func__, DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS);
	RETURN_IF(ret == -ERESTARTSYS, -EINTR, "%s %s Receive call was interrupted\n", LOG_NAME, __func__);
	return 0;
}
