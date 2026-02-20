#ifndef BORE_VGPIO_SEAMS_H
#define BORE_VGPIO_SEAMS_H

#include "../bore_sfi_virtual_gpio.h"

int vs_stub_port_init(int port);
int vs_stub_port_deinit(int port);

int vs_get_direction_gc(struct gpio_chip *gc, unsigned int offset);
int vs_direction_input(struct gpio_chip *gc, unsigned int offset);
int vs_gc_get(struct gpio_chip *gc, unsigned int offset);

#endif  /* BORE_VGPIO_SEAMS_H */