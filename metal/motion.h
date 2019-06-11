

#ifndef METAL__MOTION_H
#define METAL__MOTION_H

struct metal_motion;

struct motion_actuator {
  int acceleration;
};

struct motion_sensor {
  int frontDistance;
  int backDistance;
  int velocity;
};

struct metal_motion_vtable {
  void (*init)(struct metal_motion *motion);
  int (*actuate)(struct metal_motion *motion);
  int (*sense)(struct metal_motion *motion);
  struct metal_interrupt* (*interrupt)(struct metal_motion *motion);
  int (*get_interrupt_id)(struct metal_motion *motion);
};

struct metal_motion {
  struct motion_actuator actuator;
  struct motion_sensor sensor;

  const struct metal_motion_vtable *vtable;
};

struct metal_motion *metal_motion_get_device(int device_num);

void metal_motion_init(struct metal_motion *motion);

int metal_motion_actuate(struct metal_motion *motion);

int metal_motion_sense(struct metal_motion *motion);

struct metal_interrupt* metal_motion_interrupt(struct metal_motion *motion);

int metal_motion_get_interrupt_id(struct metal_motion *motion);

#endif /* METAL__MOTION_H */
