#include "quaternion_spring.h"

#include <math.h>

#include "quaternion.h"
#include "vector3.h"


// concern: floats may not provide enough accuracy for expf
void evaluate_spring(
    const QuaternionSpring* self, 
    const double now, 
    Quaternion* out_position,
    Vector3* out_velocity
) {
    const Quaternion current_position = self->position;
    const Quaternion current_target = self->target;
    const Vector3 current_velocity = self->velocity;
    const float damping = self->damping;
    const float speed = self->speed;
    
    const float dt = speed * (float)(now - self->_time);
    const float damping_squared = damping * damping;
    
    float ang_freq, sin_theta, cos_theta;
    if (damping_squared < 1) {
        ang_freq = sqrtf(1 - damping_squared);
        const float exponential = expf(-damping * dt) / ang_freq;
        const float afdt = ang_freq * dt;
        #ifdef _GNU_SOURCE
            float sin_tm, cos_tm;
            sincosf(afdt, &sin_tm, &cos_tm);
            sin_theta = exponential * sin_tm;
            cos_theta = exponential * cos_tm;
        #else
            sin_theta = exponential * sinf(afdt);
            cos_theta = exponential * cosf(afdt);
        #endif
    } else if (damping_squared == 1) {
        ang_freq = 1;
        const float exponential = expf(-damping * dt);
        sin_theta = exponential * dt;
        cos_theta = exponential;
    } else {
        ang_freq = sqrtf(damping_squared - 1);
        const float ang_freq_2 = 1 / (2 * ang_freq);
        const float m_damping = -damping;
        const float u = expf((m_damping + ang_freq) * dt) * ang_freq_2;
        const float v = expf((m_damping - ang_freq) * dt) * ang_freq_2;
        sin_theta = u - v;
        cos_theta = u + v;
    }
    
    if (out_position) {
        const float pull_to_target = 1 - (
            ang_freq * cos_theta + damping * sin_theta
        );
        const float vel_pos_push = sin_theta / speed;
        
        const Quaternion pos_quat = quaternion_slerp(
            &current_position, &current_target, pull_to_target
        );
        *out_position = quaternion_integrate(
            &pos_quat, &current_velocity, vel_pos_push
        );
    }
    
    if (out_velocity) {
        const float vel_push_rate = speed * sin_theta;
        const float velocity_decay = ang_freq * cos_theta - damping * sin_theta;
        const Quaternion dif_quat = quaternion_difference(
            &current_position, &current_target
        );
        const Vector3 euler_vec = quaternion_to_euler_vector(&dif_quat);
        const Vector3 vel_push = vector3_scale(&euler_vec, vel_push_rate);
        const Vector3 vel_decay = vector3_scale(&current_velocity, velocity_decay);
    
        *out_velocity = vector3_add(&vel_push, &vel_decay);
    }
}

inline double time_now(const QuaternionSpring* self) {
    return self->clock(self->clock_state);
}


void quaternion_spring_evaluate(
    QuaternionSpring* self,
    Quaternion* out_position,
    Vector3* out_velocity
) {
    double now = time_now(self);
    evaluate_spring(self, now, out_position, out_velocity);
    self->_time = now;
}

void quaternion_spring_evaluate_npv(
    QuaternionSpring* self
) {
    double now = time_now(self);
    self->_time = now;
}


void quaternion_spring_set_position(
    QuaternionSpring* self,
    const Quaternion* position
) {
    double now = time_now(self);
    evaluate_spring(self, now, NULL, &(self->velocity));
    self->position = *position;
    self->_time = now;
}


void quaternion_spring_set_target(
    QuaternionSpring* self,
    const Quaternion* target
) {
    double now = time_now(self);
    evaluate_spring(self, now, &(self->position), &(self->velocity));
    self->target = *target;
    self->_time = now;
}


void quaternion_spring_set_velocity(
    QuaternionSpring* self,
    const Vector3* velocity
) {
    double now = time_now(self);
    evaluate_spring(self, now, &(self->position), NULL);
    self->velocity = *velocity;
    self->_time = now;
}


void quaternion_spring_set_damping(
    QuaternionSpring* self,
    const float damping
) {
    double now = time_now(self);
    evaluate_spring(self, now, &(self->position), &(self->velocity));
    self->damping = damping;
    self->_time = now;
}


void quaternion_spring_set_speed(
    QuaternionSpring* self,
    const float speed
) {
    double now = time_now(self);
    evaluate_spring(self, now, &(self->position), &(self->velocity));
    self->speed = speed;
    self->_time = now;
}

void quaternion_spring_set_clock(
    QuaternionSpring* self,
    const double (*clock)(void*),
    const void* clock_state
) {
    double now = time_now(self);
    evaluate_spring(self, now, &(self->position), &(self->velocity));
    self->clock = clock;
    self->_time = clock(clock_state);
}


void quaternion_spring_reset(
    QuaternionSpring* self,
    const Quaternion* optional_target
) {
    Quaternion target = optional_target ? *optional_target : self->_initial;
    self->_initial = target;
    self->position = target;
    self->target = target;
    self->velocity = VECTOR3_ZERO;
}


void quaternion_spring_impulse(
    QuaternionSpring* self,
    const Vector3* impulse
) {
    self->velocity = vector3_add(&(self->velocity), impulse);
}


void quaternion_spring_time_skip(
    QuaternionSpring* self,
    const double delta
) {
    double now = time_now(self);
    evaluate_spring(self, now + delta, &(self->position), &(self->velocity));
    self->_time = now;
}

