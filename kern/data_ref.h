#ifndef DATA_REF_H
#define DATA_REF_H

#include <linux/spinlock.h>
#include <linux/refcount.h>
#include <linux/slab.h>

/**
 * About: Global data publication helper for process context
 * Features:
 *   - Give possibility to publish state to global state with custom initialization/destruction in multicore environment
 *   - Give ref-counting functionality to prevent usage of dangling pointers at destruction time
 *   - Give possibility to wait while all users release data
 *   - Acquire/Put allowed to be called from sleepable and atomic context. Destruction is deferred
 */

struct data_refcount_t;

typedef void (*data_ref_release_callback_t)(struct data_refcount_t *obj);

struct data_refcount_t {
	refcount_t refcnt;
	void *user_data;
	data_ref_release_callback_t release;
};

struct data_ref_t {
	spinlock_t lock;
	void *obj;

	/* Release chain */
	struct completion released;
	struct work_struct work;
	data_ref_release_callback_t release_detached;
	struct data_refcount_t *obj_detached;
};

void drf_work_handler(struct work_struct *work);

#define DEFINE_DATA_REF(name)										\
	struct data_ref_t name = {										\
		.lock = __SPIN_LOCK_UNLOCKED(name.lock),					\
		.obj = NULL,												\
		.released = COMPLETION_INITIALIZER(name.released),			\
		.work = __WORK_INITIALIZER(name.work, drf_work_handler),	\
		.release_detached = NULL,									\
		.obj_detached = NULL										\
	}

/* Initialization */
int drf_assign_once(struct data_ref_t *dref, void *user_data,
		data_ref_release_callback_t user_release);

/* Acquire user data */
void *drf_acquire(struct data_ref_t *dref);
int drf_put(struct data_ref_t *dref);

/* Wait for some time while ref will be released */
int drf_destroy(struct data_ref_t *dref);

#endif  /* DATA_REF_H */
