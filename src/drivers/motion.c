#include <metal/io.h>
#include <metal/motion.h>
#include <metal/drivers/motion.h>

#include <stdint.h>

/* Register byte offsets */
#define MOTION_REG_ACTUATOR_COUNT 0x000
#define MOTION_REG_ACCELERATION   0x008
#define MOTION_REG_ACTUATE        0x010
#define MOTION_REG_SENSOR_COUNT   0x018
#define MOTION_REG_FRONT_DISTANCE 0x020
#define MOTION_REG_BACK_DISTANCE  0x028
#define MOTION_REG_VELOCITY       0x030
#define MOTION_REG_SENSE          0x038

#define MOTION_REG(offset) (((uint64_t)(((struct __metal_driver_motion *)(motion))->control_base) + offset))
#define MOTION_REGW(offset) (__METAL_ACCESS_ONCE((__metal_io_u64 *)MOTION_REG(offset)))

void __metal_driver_motion_init(struct metal_motion *m)
{
  struct __metal_driver_motion *motion = (void *)m;
  // wait for actuator and sensor queues to drain
  while (MOTION_REGW(MOTION_REG_ACTUATOR_COUNT) > 0) {
    asm("nop");
  }
  while (MOTION_REGW(MOTION_REG_SENSOR_COUNT) > 0) {
    MOTION_REGW(MOTION_REG_SENSE) = 0;
  }
}

int __metal_driver_motion_actuate(struct metal_motion *m)
{
  struct __metal_driver_motion *motion = (void *)m;
  // set acceleration
  MOTION_REGW(MOTION_REG_ACCELERATION) = motion->motion.actuator.acceleration;
  // wait for queue not to be full
  while (MOTION_REGW(MOTION_REG_ACTUATOR_COUNT) == 8)
    ;
  // add actuation to queue
  MOTION_REGW(MOTION_REG_ACTUATE) = 0;
}

int __metal_driver_motion_sense(struct metal_motion *m)
{
  struct __metal_driver_motion *motion = (void *)m;
  // wait for queue to not be empty
  while (MOTION_REGW(MOTION_REG_SENSOR_COUNT) == 0)
    ;
  // save sensor values in struct
  motion->motion.sensor.frontDistance = MOTION_REGW(MOTION_REG_FRONT_DISTANCE);
  motion->motion.sensor.backDistance = MOTION_REGW(MOTION_REG_BACK_DISTANCE);
  motion->motion.sensor.velocity = MOTION_REGW(MOTION_REG_VELOCITY);
  // remove entry from queue
  MOTION_REGW(MOTION_REG_SENSE) = 0;
}

struct metal_interrupt *
__metal_driver_motion_interrupt_controller(struct metal_motion *m)
{
  struct __metal_driver_motion *motion = (void *)m;
  return (struct metal_interrupt *)motion->interrupt_parent;
}

int __metal_driver_motion_get_interrupt_id(struct metal_motion *m)
{
  struct __metal_driver_motion *motion = (void *)m;
  return (motion->interrupt_line + 0); // METAL_INTERRUPT_ID_GL0);
}
