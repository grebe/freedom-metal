/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/drivers/tohost.h>

const struct metal_uart_vtable tohost_uart_vtable = {
  .init = tohost_init,
  .putc = tohost_putc,
  .getc = tohost_getc,
  .get_baud_rate = tohost_get_baud_rate,
  .set_baud_rate = tohost_set_baud_rate,
  .controller_interrupt = tohost_controller_interrupt,
  .get_interrupt_id = tohost_get_interrupt_id,
};

void tohost_init(struct metal_uart *uart, int baud_rate)
{
  return;
}

static uintptr_t syscall(uintptr_t which, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
  volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();

  tohost = (uintptr_t)magic_mem;
  while (fromhost == 0)
    ;
  fromhost = 0;

  __sync_synchronize();
  return magic_mem[0];
}

int tohost_putc(struct metal_uart *uart, unsigned char c)
{
  static char buf[64] __attribute__((aligned(64)));
  static int buflen = 0;

  buf[buflen++] = c;

  if (c == '\n' || buflen == sizeof(buf))
  {
    syscall(64, 1, (uintptr_t)buf, buflen);
    buflen = 0;
  }

  return 0;

}

int tohost_getc(struct metal_uart *uart, unsigned char *c)
{
  *c = 0;
}

int tohost_get_baud_rate(struct metal_uart *uart)
{
  return 0;
}

int tohost_set_baud_rate(struct metal_uart *uart, int baud_rate)
{
  return 0;
}

struct metal_interrupt *tohost_controller_interrupt(struct metal_uart *uart)
{
  return NULL;
}

int tohost_get_interrupt_id(struct metal_uart *uart)
{
  return 0;
}
