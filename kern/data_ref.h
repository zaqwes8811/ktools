#ifndef KERN_DATA_REF_H
#define KERN_DATA_REF_H

#include <linux/spinlock.h>
#include <linux/refcount.h>
#include <linux/slab.h>

#define DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS  (1000)

typedef void (*data_ref_release_callback_t)(void *obj);

struct data_refcount_t {
	refcount_t refcnt;
	void *data;
	data_ref_release_callback_t release;
};

struct data_ref_t {
	spinlock_t lock;
	void *data;

	/* Release chain */
	struct completion released;
	struct work_struct work;
	data_ref_release_callback_t release_detached;
	struct data_refcount_t *obj_detached;
};

static void drf_work_handler(struct work_struct *work)
{
	struct data_ref_t *ref = container_of(work, struct data_ref_t, work);

	if (ref->release_detached && ref->obj_detached) {
		ref->release_detached(ref->obj_detached);
		kfree(ref->obj_detached);
	}

	complete(&ref->released);
}

#define DEFINE_DATA_REF(name) \
	struct data_ref_t name = { \
		.lock = __SPIN_LOCK_UNLOCKED(name.lock), \
		.data = NULL, \
		.released = COMPLETION_INITIALIZER(name.released), \
		.work = __WORK_INITIALIZER(name.work, drf_work_handler), \
		.release_detached = NULL, \
		.obj_detached = NULL \
	}

static inline void *drf_get(struct data_ref_t *dref)
{
	void *data;

	if (WARN_ON_ONCE(!dref))
		return NULL;

	spin_lock(&dref->lock);
	data = dref->data;
	spin_unlock(&dref->lock);
	return data;
}

static inline void drf_set(struct data_ref_t *dref, void *data)
{
	if (WARN_ON_ONCE(!dref))
		return;

	spin_lock(&dref->lock);
	dref->data = data;
	spin_unlock(&dref->lock);
}

static inline struct data_refcount_t *drf_acquire(struct data_ref_t *dref)
{
	struct data_refcount_t *obj;

	if (WARN_ON_ONCE(!dref))
		return NULL;

	spin_lock(&dref->lock);
	obj = dref->data;
	if (!(obj && refcount_inc_not_zero(&obj->refcnt))) {
		spin_unlock(&dref->lock);
		return NULL;
	}
	spin_unlock(&dref->lock);
	return obj;
}

static inline void drf_put(struct data_ref_t *dref)
{
	data_ref_release_callback_t release = NULL;
	struct data_refcount_t *obj;

	if (WARN_ON_ONCE(!dref))
		return;

	spin_lock(&dref->lock);
	obj = dref->data;
	if (!obj) {
		spin_unlock(&dref->lock);
		return;
	}

	if (refcount_dec_and_test(&obj->refcnt)) {
		if (obj->release) {
			release = obj->release;
			obj->release = NULL;
			dref->data = NULL;
		}
	}
	spin_unlock(&dref->lock);

	if (release) {
		dref->obj_detached = obj;
		dref->release_detached = release;

		schedule_work(&dref->work);  /* Destroy out of potential atomic context */
	}
}

static inline void drf_destroy(struct data_ref_t *dref)
{
	const unsigned long timeout = msecs_to_jiffies(DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS);

	if (WARN_ON_ONCE(!dref))
		return;

	if (wait_for_completion_timeout(&dref->released, timeout) == 0) {
		pr_err("Operation timed out after %d ms\n", DRF_DEFAULT_RELEASE_WAIT_TIMEOUT_MS);
	}
}

#endif  /* KERN_DATA_REF_H */