#include "types.h"

// Never write to struct fields directly.
// Always call functions to update fields.
// It's ok to read from the fields once they have been evaluated.
// Fields prefixed with an underscore are not be read.

//https://linux.die.net/man/3/clock_gettime

typedef struct QuaternionSpring {
    Quaternion position;
    Quaternion target;
    Vector3 velocity;
    float damping;
    float speed;
    double (*clock)(void*);
    void* clock_state;
    double _time;
} QuaternionSpring;


void quaternion_spring_new(
    const Quaternion* intial,
    const float damping,
    const float speed,
    double (*clock)(void*),
    void* clock_state,
    QuaternionSpring* out_spring
);


void quaternion_spring_evaluate(
    QuaternionSpring* self
);


Quaternion quaternion_spring_get_position(
    QuaternionSpring* self
);


void quaternion_spring_set_position(
    QuaternionSpring* self,
    const Quaternion* position
);


void quaternion_spring_set_target(
    QuaternionSpring* self,
    const Quaternion* target
);


Vector3 quaternion_spring_get_velocity(
    QuaternionSpring* self
);


void quaternion_spring_set_velocity(
    QuaternionSpring* self,
    const Vector3* velocity
);


void quaternion_spring_set_damping(
    QuaternionSpring* self,
    const float damping
);


void quaternion_spring_set_speed(
    QuaternionSpring* self,
    const float speed
);


void quaternion_spring_reset(
    QuaternionSpring* self,
    const Quaternion* optional_target
);


void quaternion_spring_impulse(
    QuaternionSpring* self,
    Vector3* impulse
);


void quaternion_spring_time_skip(
    QuaternionSpring* self,
    float delta
);


