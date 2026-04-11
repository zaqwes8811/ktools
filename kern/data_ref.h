#ifndef KERN_DATA_REF_H
#define KERN_DATA_REF_H

#include <linux/spinlock.h>
#include <linux/refcount.h>
#include <linux/slab.h>

typedef void (*data_ref_release_callback_t)(void *obj);

struct data_refcount_t {
	refcount_t refcnt;
	void *data;
	data_ref_release_callback_t release;
};

struct data_ref_t {
	spinlock_t lock;
	int users;  // TODO() Conntect
	void *data;
	struct completion released;
};

#define DEFINE_DATA_REF(name) \
	struct data_ref_t name = { \
		.lock = __SPIN_LOCK_UNLOCKED(name.lock), \
		.users = 0, \
		.data = NULL, \
		.released = COMPLETION_INITIALIZER(name.released) \
	}

static inline void *drf_get(struct data_ref_t *dref)
{
	void *data;

	BUG_ON(dref == NULL);

	spin_lock(&dref->lock);
	data = dref->data;
	spin_unlock(&dref->lock);
	return data;
}

static inline void drf_set(struct data_ref_t *dref, void *data)
{
	BUG_ON(dref == NULL);

	spin_lock(&dref->lock);
	dref->data = data;
	spin_unlock(&dref->lock);
}

static inline struct data_refcount_t *drf_acquire(struct data_ref_t *dref)
{
	struct data_refcount_t *obj;

	spin_lock(&dref->lock);
	obj = dref->data;
	if (!(obj && refcount_inc_not_zero(&obj->refcnt))) {
		spin_unlock(&dref->lock);
		return NULL;
	}
	++dref->users;
	spin_unlock(&dref->lock);
	return obj;
}

static inline void drf_put(struct data_ref_t *dref)
{
	data_ref_release_callback_t release = NULL;
	struct data_refcount_t *obj;

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
			dref->data = NULL;  /* Detach object */
		}
	}
	--dref->users;
	spin_unlock(&dref->lock);

	// TODO() Can't called in non-process context
	if (release) {
		// TODO() Protect module code unloading?
		release(obj);
		kfree(obj);
	}
}

static inline void drf_destroy(struct data_ref_t *dref)
{
	// TODO() Just check
}

#endif  /* KERN_DATA_REF_H */