
#ifndef QUATERNION_H
#define QUATERNION_H

#include <stddef.h>
#include "types.h"


// Constants

extern const Quaternion QUATERNION_IDENTITY;
extern const Quaternion QUATERNION_ZERO;

// Constructors

static inline Quaternion quaternion_new(
    const float x, 
    const float y, 
    const float z, 
    const float w
) {
    return (Quaternion) { x, y, z, w };
}

static inline Quaternion quaternion_copy(
    const Quaternion* self
) {
    return (Quaternion) { self->x, self->y, self->z, self->w };
}

Quaternion quaternion_from_axis_angle(
    const Vector3* axis, 
    const float angle
);

Quaternion quaternion_from_axis_angle_safe(
    const Vector3* axis, 
    const float epsilon,
    const float angle
);

Quaternion quaternion_from_euler_vector(
   const Vector3* euler_vector,
   const float epsilon
);

Quaternion quaternion_from_matrix(
    const Matrix* matrix
);

Quaternion quaternion_from_matrix_fast(
    const Matrix* matrix
);

Quaternion quaternion_from_vectors(
    const Vector3* vx,
    const Vector3* vy,
    const Vector3* vz
);

Quaternion quaternion_from_vectors_fast(
    const Vector3* vX,
    const Vector3* vY,
    const Vector3* vZ
);

Quaternion quaternion_look_at(
    const Vector3* from,
    const Vector3* look_at,
    const Vector3* up
);

Quaternion quaternion_from_euler_angles_xyz(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_euler_angles_xzy(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_euler_angles_yxz(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_euler_angles_yzx(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_euler_angles_zxy(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_euler_angles_zyx(
    const float rx,
    const float ry,
    const float rz
);

Quaternion quaternion_from_vector(
    const Vector3* vector,
    const float w
);

float random_float();
float random_float_r(void* seed);

Quaternion quaternion_random(float (*random_float_generator)());

Quaternion quaternion_random_state(
    float (*random_float_generator)(void*), 
    void* state
);





// Operations

Quaternion quaternion_add(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_sub(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_mul(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_div(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_unm(
    const Quaternion* q0
);

Quaternion quaternion_pow(
    const Quaternion* q0,
    const float pow
);

int quaternion_lt(
    const Quaternion* q0,
    const Quaternion* q1
);

int quaternion_le(
    const Quaternion* q0,
    const Quaternion* q1
);

int quaternion_eq(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_scale(
    const Quaternion* q0,
    const float scale
);

Quaternion quaternion_mul_matrix_l(
    const Quaternion* q0,
    const Matrix* matrix
);

Quaternion quaternion_mul_matrix_r(
    const Matrix* matrix,
    const Quaternion* q0
);

Vector3 quaternion_rotate_vector(
    const Quaternion* q0,
    const Vector3* vector
);

Quaternion quaternion_combine_imaginary(
    const Quaternion* q0,
    const Vector3* vector
);

Quaternion quaternion_scale_inv(
    const Quaternion* q0,
    const float scale
);


// Methods

Quaternion quaternion_unit(
    const Quaternion* q0
);

float quaternion_length(
    const Quaternion* q0
);

float quaternion_length_acc(
    const Quaternion* q0
);

float quaternion_length_squared(
    const Quaternion* q0
);

Quaternion quaternion_exp(
    const Quaternion* q0
);

Quaternion quaternion_exp_map(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_exp_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_log(
    const Quaternion* q0
);

Quaternion quaternion_log_map(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_log_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_hypot(
    const Quaternion* q0
);

Quaternion quaternion_normalize(
    const Quaternion* q0
);

int quaternion_is_unit(
    const Quaternion* q0
);

float quaternion_dot(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_conjugate(
    const Quaternion* q0
);

Quaternion quaternion_inverse(
    const Quaternion* q0
);

Quaternion quaternion_negate(
    const Quaternion* q0
);

Quaternion quaternion_difference(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_distance(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_distance_sym(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_distance_chord(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_distance_abs(
    const Quaternion* q0,
    const Quaternion* q1
);

Quaternion quaternion_slerp(
    const Quaternion* q0,
    const Quaternion* q1,
    const float alpha
);

Quaternion quaternion_slerp_identity(
    const Quaternion* q1,
    const float alpha
);


struct SlerpState {
    const Quaternion q0;
    const Quaternion q1;
    const float dot;
    const float theta_0;
    const float sin_theta_0;
};

void quaternion_slerp_function_init(
    const Quaternion* q0,
    const Quaternion* q1,
    struct SlerpState* out_slerp_state
);

Quaternion quaternion_slerp_function(
    const struct SlerpState* slerp_state,
    const float alpha
);

size_t quaternion_get_intermediates_count(
    const size_t number,
    const int include_endpoints
);

void quaternion_intermediates(
    const Quaternion* q0,
    const Quaternion* q1,
    const size_t number,
    const int include_endpoints,
    Quaternion out_intermediates[]
);

Quaternion quaternion_derivative(
    const Quaternion* q0,
    const Vector3* rate
);

Quaternion quaternion_integrate(
    const Quaternion* q0,
    const Vector3* rate,
    const float timestep
);

Quaternion quaternion_angular_velocity(
    const Quaternion* q0,
    const Quaternion* q1,
    const float timestep
);

Quaternion quaternion_minimal_rotation(
    const Quaternion* q0,
    const Quaternion* q1
);

int quaternion_approx_eq(
    const Quaternion* q0,
    const Quaternion* q1,
    const float epsilon
);

int quaternion_is_nan(
    const Quaternion* q0
);


// Deconstructors

void quaternion_to_matrix(
    const Quaternion* q0,
    const Vector3* position, //optional
    Matrix* out
);

void quaternion_to_matrix_vectors(
    const Quaternion* q0,
    Vector3* out_vx,
    Vector3* out_vy,
    Vector3* out_vz
);

float quaternion_to_axis_angle(
    const Quaternion* q0,
    Vector3* out_axis
);

Vector3 quaternion_to_euler_vector(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_xyz(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_xzy(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_yxz(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_yzx(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_zxy(
    const Quaternion* q0
);

EulerAngles quaternion_to_euler_angles_zyx(
    const Quaternion* q0
);

Vector3 quaternion_vector(
    const Quaternion* q0
);

float quaternion_scalar(
    const Quaternion* q0
);

Quaternion quaternion_imaginary(
    const Quaternion* q0
);

// CALLER IS RESPONSIBLE FOR FREEING
char* quaternion_to_string(
    const Quaternion* q0,
    const unsigned int decimal_places,
    const char formatter
);

#endif
