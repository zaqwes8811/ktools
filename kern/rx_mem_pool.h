
#ifndef RX_MEM_POOL_H
#define RX_MEM_POOL_H

#include <soc/atom/sfi_sys_primitives.h>
#include <soc/atom/vector.h>

/*
 * Usecase 0:
 *   - Single HardIrd writter and single Process reader (spin_lock and spin_lock_irqsave)
 *
 * Usecase 1:
 *   - Single Process writer and single process reader (spin_lock and spin_lock)
 */

#define RX_DEFAULT_MEM_POOL_SIZE (16)

typedef void (*rx_mem_pool_cb)(struct work_struct *);

struct rx_mem_pool_buffer_t {
	unsigned char *addr;
	unsigned int cur_size;
	unsigned int max_size;
};

struct rx_mem_pool_cell_t {
	int index;

	bool locked;
	struct work_struct proc_work;

	struct rx_mem_pool_buffer_t buffer;
	void* user_data;

	spinlock_t lock;
};

struct rx_mem_pool_t {
	struct rx_mem_pool_cell_t *cells;
	int cells_count;
};

int rmp_init(struct rx_mem_pool_t *self, int max_cell_size,
	int cells_count, rx_mem_pool_cb proc_cb, void* user_data);
int rmp_deinit(struct rx_mem_pool_t *self);

int rmp_try_claim_and_fill(
	struct rx_mem_pool_t *self, const unsigned char *data, size_t data_size, bool irqsave,
	struct rx_mem_pool_cell_t **cell);

int rmp_cancel_all_tasks(struct rx_mem_pool_t *self);
int rmp_release_by_idx(struct rx_mem_pool_t *pool, size_t index, bool irqsave);

int rmp_unload_and_release_cell(struct rx_mem_pool_cell_t *self,
		struct vector_view_u8_t out_buffer, bool irqsave, size_t *written);
int rmp_unload_and_release_cell_by_index(struct rx_mem_pool_t *self,
		struct vector_view_u8_t out_buffer, bool irqsave, size_t *written, int index);

#endif  /* RX_MEM_POOL_H */