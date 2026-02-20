#include "vgpio_seams.h"

#define ASVG_MAX_PORTS_COUNT (128)
#define ASVG_GPIO_NR 8
#define LOG_NAME "[vgpio-seams]"

struct asvg_stub_port_t {
	struct kobject kobj_value;
	int state[ASVG_GPIO_NR];
	int direction[ASVG_GPIO_NR];

	struct asvg_drv_t *uplink;
};

static struct asvg_stub_port_t stub_ports[ASVG_MAX_PORTS_COUNT];

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%s\n", "unused");
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
					const char *buf, size_t count)
{
	struct asvg_stub_port_t *stub_port =
		container_of(kobj, struct asvg_stub_port_t, kobj_value);
	int pin;

	sscanf(buf, "%du", &pin);

	if (stub_port->state[pin] == 0)
		stub_port->state[pin] = 1;
	else
		stub_port->state[pin] = 0;

	(void) asvg_notify_all_isr(stub_port->uplink, pin);
	return count;
}

static struct kobj_attribute toggle_pin_attribute =__ATTR(toggle_pin, 0660, foo_show,
                                                   foo_store);

static struct kobj_type asvg_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
};

int vs_stub_port_init(int port)
{
	int ret;
	char wq_name[128];

	memset(wq_name, 0x00, sizeof(wq_name));
	ret = snprintf(wq_name, sizeof(wq_name) - 1U, "%s%d", "vgpio", port);

	ret = kobject_init_and_add(&stub_ports[port].kobj_value, &asvg_ktype, NULL, "%s", wq_name);
	RETURN_IF(ret < 0, ret,	"%s %s Can't create kobj wq name for port: %d, ec: %d\n",
			LOG_NAME, __func__, port, ret);

	ret = sysfs_create_file(&stub_ports[port].kobj_value, &toggle_pin_attribute.attr);
	if (ret) {
		pr_debug("failed to create the foo file in /sys/kernel/kobject_example \n");
		return ret;
	}

	return 0;
}

int vs_stub_port_deinit(int port)
{
	kobject_put(&stub_ports[port].kobj_value);
	return 0;
}

int vs_get_direction_gc(struct gpio_chip *gc, unsigned int offset)
{
    struct asvg_drv_t *self = gpiochip_get_data(gc);

	stub_ports[self->port].uplink = self;
	return stub_ports[self->port].direction[offset];
}

int vs_direction_input(struct gpio_chip *gc, unsigned int offset)
{
    struct asvg_drv_t *self = gpiochip_get_data(gc);
	stub_ports[self->port].direction[offset] = GPIO_LINE_DIRECTION_IN;
	return 0;
}

int vs_gc_get(struct gpio_chip *gc, unsigned int offset)
{
	struct asvg_drv_t *self = gpiochip_get_data(gc);
	return stub_ports[self->port].state[offset];
}