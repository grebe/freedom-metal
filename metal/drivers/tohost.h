
#include <metal/uart.h>
#include <stdint.h>

#ifndef METAL__TOHOST_H
#define METAL__TOHOST_H

extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;

extern const struct metal_uart_vtable tohost_uart_vtable;

void tohost_init(struct metal_uart *uart, int baud_rate);
int tohost_putc(struct metal_uart *uart, unsigned char c);
int tohost_getc(struct metal_uart *uart, unsigned char *c);
int tohost_get_baud_rate(struct metal_uart *uart);
int tohost_set_baud_rate(struct metal_uart *uart, int baud_rate);
struct metal_interrupt *tohost_controller_interrupt(struct metal_uart *uart);
int tohost_get_interrupt_id(struct metal_uart *uart);

#endif /* METAL__TOHOST_H */

