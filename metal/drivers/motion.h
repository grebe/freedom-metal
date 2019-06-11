

#ifndef METAL__DRIVERS__MOTION_H
#define METAL__DRIVERS__MOTION_H

#include <metal/compiler.h>
#include <metal/motion.h>

struct __metal_driver_vtable_motion {
  const struct metal_motion_vtable motion;
};

struct __metal_driver_motion;

void __metal_driver_motion_init(struct metal_motion *motion);
int __metal_driver_motion_actuate(struct metal_motion *motion);
int __metal_driver_motion_sense(struct metal_motion *motion);
struct metal_interrupt* __metal_driver_motion_interrupt_controller(struct metal_motion *motion);
int __metal_driver_motion_get_interrupt_id(struct metal_motion *motion);

__METAL_DECLARE_VTABLE(__metal_driver_vtable_motion) = {
  .motion.init = __metal_driver_motion_init,
  .motion.actuate = __metal_driver_motion_actuate,
  .motion.sense = __metal_driver_motion_sense,
  .motion.interrupt = __metal_driver_motion_interrupt_controller,
  .motion.get_interrupt_id = __metal_driver_motion_get_interrupt_id,
};

struct __metal_driver_motion {
  struct metal_motion motion;
  const struct __metal_driver_vtable_motion *vtable;
  const unsigned long control_base;
  const unsigned long control_size;
  struct metal_interrupt *interrupt_parent;
  const int num_interrupts;
  const int interrupt_line;
};

#endif /* METAL__DRIVERS__MOTION_H */

