

#include <metal/machine.h>
#include <metal/motion.h>

struct metal_motion *metal_motion_get_device(int device_num)
{
  if (device_num >= __METAL_DT_MAX_MOTIONS) {
    return NULL;
  }

  return (struct metal_motion *) (__metal_motion_table[device_num]);
}

void metal_motion_init(struct metal_motion *motion)
{
  motion->vtable->init(motion);
}

int metal_motion_actuate(struct metal_motion *motion)
{
  return motion->vtable->actuate(motion);
}

int metal_motion_sense(struct metal_motion *motion)
{
  return motion->vtable->sense(motion);
}

struct metal_interrupt* metal_motion_interrupt(struct metal_motion *motion)
{
  return motion->vtable->interrupt(motion);
}

int metal_motion_get_interrupt_id(struct metal_motion *motion)
{
  return motion->vtable->get_interrupt_id(motion);
}

