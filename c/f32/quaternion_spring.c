#include "quaternion_spring.h"
#include "quaternion.h"
#include "vector3.h"
#include "math.h"


void position_velocity(
    QuaternionSpring* self, 
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
        // I have no idea if this will work or not.
        #ifdef _GNU_SOURCE
            float sin, cos;
            sincosf(afdt, &sin, &cos);
            sin_theta = exponential * sin;
            cos_theta = exponential * cos;
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
    
    const float pull_to_target = 1 - (
        ang_freq * cos_theta + damping * sin_theta
    );
    const float vel_pos_push = sin_theta / speed;
    const float vel_push_rate = speed * sin_theta;
    const float velocity_decay = ang_freq * cos_theta - damping * sin_theta;
    
    const Quaternion pos_quat = quaternion_slerp(
        &current_position, &current_target, pull_to_target
    );
    *out_position = quaternion_integrate(
        &pos_quat, &current_velocity, vel_pos_push
    );
    
    const Quaternion dif_quat = quaternion_difference(
        &current_position, &current_target
    );
    const Vector3 euler_vec = quaternion_to_euler_vector(&dif_quat);
    const Vector3 vel_push = vector3_scale(&euler_vec, vel_push_rate);
    const Vector3 vel_decay = vector3_scale(&current_velocity, velocity_decay);
    
    *out_velocity = vector3_add(&vel_push, &vel_decay);
}


void quaternion_spring_evaluate(
    QuaternionSpring* self
) {
    
}


Quaternion quaternion_spring_get_position(
    QuaternionSpring* self
) {
    
}


void quaternion_spring_set_position(
    QuaternionSpring* self,
    const Quaternion* position
) {
    
}


void quaternion_spring_set_target(
    QuaternionSpring* self,
    const Quaternion* target
) {
    
}


Vector3 quaternion_spring_get_velocity(
    QuaternionSpring* self
) {
    
}


void quaternion_spring_set_velocity(
    QuaternionSpring* self,
    const Vector3* velocity
) {
    
}


void quaternion_spring_set_damping(
    QuaternionSpring* self,
    const float damping
) {
    
}


void quaternion_spring_set_speed(
    QuaternionSpring* self,
    const float speed
) {
    
}


void quaternion_spring_reset(
    QuaternionSpring* self,
    const Quaternion* optional_target
) {
    
}


void quaternion_spring_impulse(
    QuaternionSpring* self,
    Vector3* impulse
) {
    
}


void quaternion_spring_time_skip(
    QuaternionSpring* self,
    float delta
) {
    
}

