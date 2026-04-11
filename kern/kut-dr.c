#include "data_ref.h"

#include <soc/atom/sfi_sys_primitives.h>

#include <kunit/test.h>

#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/slab.h>

#define LOG_NAME "[kt]"

static DEFINE_DATA_REF(g_dref);

static void kut_obj_release(void *obj)
{
	pr_err("Release");
}

static int usage(void)
{
	struct data_refcount_t *obj = drf_acquire(&g_dref);

	VALIDATE_ARGPTR(obj);

	/* Safe usige */

	drf_put(&g_dref);
	return 0;
}

static void test_refcount(struct kunit *test)
{
	struct data_refcount_t *obj;

	obj = kmalloc(sizeof(*obj), GFP_KERNEL);
	KUNIT_ASSERT_TRUE(test, obj != NULL);

	/* Initialization */
	refcount_set(&obj->refcnt, 1);
	obj->release = kut_obj_release;
	obj->data = NULL;

	/* Publication */
	drf_set(&g_dref, obj);

	(void) usage();

	drf_put(&g_dref);  /* Final clean */

	(void) usage();

	drf_destroy(&g_dref);
}

static struct kunit_case kut_cases[] = {
	KUNIT_CASE(test_refcount),
	{}
};

static struct kunit_suite kut_suite = {
	.name = "kut-dr",
	.test_cases = kut_cases,
};

kunit_test_suites(&kut_suite);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Igor Lugansky <igor.a.lugansky@ya.ru>");