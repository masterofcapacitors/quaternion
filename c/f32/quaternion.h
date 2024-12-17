
#ifndef QUATERNION_H
#define QUATERNION_H

struct Vector3;
typedef struct Vector3 Vector3;

struct Matrix;
typedef struct Matrix Matrix;

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;


// Constructors

const Quaternion quaternion_new(
    const float x, 
    const float y, 
    const float z, 
    const float w
);

const Quaternion quaternion_from_axis_angle(
    const Vector3* axis, 
    const float angle
);

const Quaternion quaternion_from_axis_angle_fast(
    const Vector3* axis, 
    const float angle
);

const Quaternion quaternion_from_euler_vector(
   const Vector3* euler_vector
);

const Quaternion quaternion_from_matrix(
    const Matrix* matrix
);

const Quaternion quaternion_from_matrix_fast(
    const Matrix* matrix
);

const Quaternion quaternion_from_vectors(
    const Vector3* vx,
    const Vector3* vy,
    const Vector3* vz
);

const Quaternion quaternion_from_vectors_fast(
    const Vector3* vX,
    const Vector3* vY,
    const Vector3* vZ
);

const Quaternion quaternion_look_at(
    const Vector3* from,
    const Vector3* look_at,
    const Vector3* up
);

const Quaternion quaternion_from_euler_angles_xyz(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_euler_angles_xzy(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_euler_angles_yxz(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_euler_angles_yzx(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_euler_angles_zxy(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_euler_angles_zyx(
    const float rx,
    const float ry,
    const float rz
);

const Quaternion quaternion_from_vector(
    const Vector3* vector,
    const float w
);

const Quaternion quaternion_random();


// Constants

extern const Quaternion QUATERNION_IDENTITY;
extern const Quaternion QUATERNION_ZERO;


// Operations

const Quaternion quaternion_add(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_sub(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_mul(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_div(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_unm(
    const Quaternion* q0
);

const Quaternion quaternion_pow(
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

const Quaternion quaternion_scale(
    const Quaternion* q0,
    const float scale
);

const Quaternion quaternion_mul_matrix_l(
    const Quaternion* q0,
    const Matrix* matrix
);

const Quaternion quaternion_mul_matrix_r(
    const Matrix* matrix,
    const Quaternion* q0
);

Vector3 quaternion_rotate_vector(
    const Quaternion* q0,
    const Vector3* vector
);

const Quaternion quaternion_combine_imaginary(
    const Quaternion* q0,
    const Vector3* vector
);

const Quaternion quaternion_scale_inv(
    const Quaternion* q0,
    const float scale
);


// Methods

const Quaternion quaternion_unit(
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

const Quaternion quaternion_exp(
    const Quaternion* q0
);

const Quaternion quaternion_exp_map(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_exp_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_log(
    const Quaternion* q0
);

const Quaternion quaternion_log_map(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_log_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
);

float quaternion_hypot(
    const Quaternion* q0
);

const Quaternion quaternion_normalize(
    const Quaternion* q0
);

int quaternion_is_unit(
    const Quaternion* q0
);

float quaternion_dot(
    const Quaternion* q0,
    const Quaternion* q1
);

const Quaternion quaternion_conjugate(
    const Quaternion* q0
);

const Quaternion quaternion_inverse(
    const Quaternion* q0
);

const Quaternion quaternion_negate(
    const Quaternion* q0
);

const Quaternion quaternion_difference(
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

const Quaternion quaternion_slerp(
    const Quaternion* q0,
    const Quaternion* q1,
    const float alpha
);

const Quaternion quaternion_slerp_identity(
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

const Quaternion quaternion_slerp_function(
    const struct SlerpState* slerp_state,
    const float alpha
);

void quaternion_intermediates(
    const Quaternion* q0,
    const Quaternion* q1,
    const size_t number,
    const int include_endpoints,
    Quaternion** out_intermediates
);

const Quaternion quaternion_derivative(
    const Quaternion* q0,
    const Vector3* rate
);

const Quaternion quaternion_integrate(
    const Quaternion* q0,
    const Vector3*,
    const float timestep
);

const Quaternion quaternion_angular_velocity(
    const Quaternion* q0,
    const Quaternion* q1,
    const float timestep
);

const Quaternion quaternion_minimal_rotation(
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

void quaternion_to_euler_vector(
    const Quaternion* q0,
    Vector3* out
);

void quaternion_to_euler_angles_xyz(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_to_euler_angles_xzy(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_to_euler_angles_yxz(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_to_euler_angles_yzx(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_to_euler_angles_zxy(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_to_euler_angles_zyx(
    const Quaternion* q0,
    float* out_rx,
    float* out_ry,
    float* out_rz
);

void quaternion_vector(
    const Quaternion* q0,
    Vector3* out
);

float quaternion_scalar(
    const Quaternion* q0
);

const Quaternion quaternion_imaginary(
    const Quaternion* q0
);

// CALLER IS RESPONSIBLE FOR FREEING
char* quaternion_to_string(
    const Quaternion* q0,
    const unsigned int decimal_places
);

#endif
