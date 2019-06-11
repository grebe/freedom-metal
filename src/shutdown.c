/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/machine.h>
#include <metal/shutdown.h>

extern inline void __metal_shutdown_exit(const struct __metal_shutdown *sd, int code);

#if defined(__METAL_DT_SHUTDOWN_HANDLE)
void metal_shutdown(int code)
{
    __metal_shutdown_exit(__METAL_DT_SHUTDOWN_HANDLE, code);
}
#else
# warning "There is no defined shutdown mechanism, metal_shutdown() will spin."
void metal_shutdown(int code)
{
    while (1) {
      __asm__ volatile ("nop");
    }
}
#endif

#if defined(TOHOST_SHUTDOWN)
void __attribute__((noreturn)) tohost_exit(const struct __metal_shutdown *sd, int code)
{
  tohost = (code << 1) | 1;
  while(1) {
    __asm__ volatile ("nop");
  }
}

const struct __metal_shutdown_vtable __tohost_shutdown_vtable = {
  .exit = tohost_exit,
};

#endif /* TOHOST_SHUTDOWN */
