#include "types.h"

// Never write to struct fields directly.
// Always call functions to update fields.
// It's ok to read from the fields once they have been evaluated.
// Fields prefixed with an underscore are not be read.

//https://linux.die.net/man/3/clock_gettime

typedef struct QuaternionSpring {
    Quaternion position;
    Quaternion target;
    Quaternion _initial;
    Vector3 velocity;
    float damping;
    float speed;
    double (*clock)(void*);
    void* clock_state;
    double _time;
} QuaternionSpring;


static inline void quaternion_spring_new(
    const Quaternion* initial,
    const float damping,
    const float speed,
    double (*clock)(void*),
    void* clock_state,
    QuaternionSpring* out_spring
) {
    out_spring->position = *initial;
    out_spring->target = *initial;
    out_spring->_initial = *initial;
    out_spring->velocity = VECTOR3_ZERO;
    out_spring->damping = damping;
    out_spring->speed = speed;
    out_spring->clock = clock;
    out_spring->clock_state = clock_state;
    out_spring->_time = clock(clock_state);
}

// Must call to get the latest position/velocity
void quaternion_spring_evaluate(
    QuaternionSpring* self,
    Quaternion* out_position,
    Vector3* out_velocity
);

// needs more testing to confirm behaviour
void quaternion_spring_evaluate_npv(
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

void quaternion_spring_set_clock(
    QuaternionSpring* self,
    const double (*clock)(void*),
    const void* clock_state
);


void quaternion_spring_reset(
    QuaternionSpring* self,
    const Quaternion* optional_target
);


void quaternion_spring_impulse(
    QuaternionSpring* self,
    const Vector3* impulse
);


void quaternion_spring_time_skip(
    QuaternionSpring* self,
    const double delta
);


