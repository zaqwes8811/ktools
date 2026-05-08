#ifndef KACTOR_H
#define KACTOR_H

#include <soc/atom/rx_mem_pool.h>

typedef void (*kactr_callback)(void *);

struct kactor_work_t {
	void *arg;
	kactr_callback cb;
};

struct kactor_t {
	struct rx_mem_pool_t rx_mem_pool;

	struct workqueue_struct *seq_q;
	bool fillable;

	struct mutex lock;
};

int ka_init(struct kactor_t *self, size_t q_depth);
int ka_deinit(struct kactor_t *self);
int ka_push(struct kactor_t *self, struct kactor_work_t w);

#endif  /* KACTOR_H */
