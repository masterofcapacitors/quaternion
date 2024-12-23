#include "quaternion.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_DEFINE_CONSTANTS
#include "math_util.h"

#include "vector3.h"


const Quaternion QUATERNION_IDENTITY = { 0, 0, 0, 1 };
const Quaternion QUATERNION_ZERO = { 0, 0, 0, 0 };

// Constructors

// Utility Functions

//
//


Quaternion quaternion_from_axis_angle(
    const Vector3* axis, 
    const float angle
) {
    float ha = angle / 2;
    Vector3 shaxis = vector3_scale(axis, sinf(ha));
    float qx = shaxis.x;
    float qy = shaxis.y;
    float qz = shaxis.z;
    float qw = cosf(ha);
    
    return quaternion_new(qx, qy, qz, qw);
}


Quaternion quaternion_from_axis_angle_safe(
    const Vector3* axis,
    const float epsilon,
    const float angle
) {
    Vector3 unit_axis = vector3_unit_default(axis, epsilon, &VECTOR3_X_AXIS);
    
    float ha = angle / 2;
    Vector3 shaxis = vector3_scale(&unit_axis, sinf(ha));
    float qx = shaxis.x;
    float qy = shaxis.y;
    float qz = shaxis.z;
    float qw = cosf(ha);
    
    return quaternion_new(qx, qy, qz, qw);
}


Quaternion quaternion_from_euler_vector(
   const Vector3* euler_vector,
   const float epsilon
) {
    float angle = vector3_magnitude(euler_vector);
    if (angle < epsilon) {
        return QUATERNION_IDENTITY;
    }
    Vector3 axis = vector3_div(euler_vector, angle);
    return quaternion_from_axis_angle(&axis, angle);
}


Quaternion quaternion_from_matrix(
    const Matrix* matrix
) {
    
}


Quaternion quaternion_from_matrix_fast(
    const Matrix* matrix
) {
    
}


Quaternion quaternion_from_vectors(
    const Vector3* vx,
    const Vector3* vy,
    const Vector3* vz
) {
    
}


Quaternion quaternion_from_vectors_fast(
    const Vector3* vX,
    const Vector3* vY,
    const Vector3* vZ
) {
    
}


Quaternion quaternion_look_at(
    const Vector3* from,
    const Vector3* look_at,
    const Vector3* up
) {
    
}


Quaternion quaternion_from_euler_angles_xyz(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_euler_angles_xzy(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_euler_angles_yxz(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_euler_angles_yzx(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_euler_angles_zxy(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_euler_angles_zyx(
    const float rx,
    const float ry,
    const float rz
) {
    
}


Quaternion quaternion_from_vector(
    const Vector3* vector,
    const float w
) {
    
}


// Assumes srand() has been called at least once.
// Not thread safe or reentrant since it relies on `rand()`.
float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

// Uses `rand_r()`. Assumes `void* seed` is castable to `unsigned int*`.
float random_float_r(void* seed) {
    return (float)rand() / (float)RAND_MAX;
    //return (float)rand_r(*((unsigned int*)seed)) / (float)RAND_MAX;
}

Quaternion quaternion_random(float (*random_float_generator)()) {
    float u = random_float_generator();
    float v = random_float_generator();
    float w = random_float_generator();
    
    float omu = 1.0f - u;
    float squ = sqrtf(u);
    float sqmu = sqrtf(omu);
    
    float tpv = TAU * v;
    float tpw = TAU * w;
    
    Quaternion out = {
        .x = sqmu * sinf(tpv),
        .y = sqmu * cosf(tpv),
        .z = squ * sinf(tpw),
        .w = squ * cosf(tpw)
    };
    
    return out;
}

// Will call the random_float_generator 3 times.
Quaternion quaternion_random_state(
    float (*random_float_generator)(void*), 
    void* state
) {
    float u = random_float_generator(state);
    float v = random_float_generator(state);
    float w = random_float_generator(state);
    
    float omu = 1.0f - u;
    float squ = sqrtf(u);
    float sqmu = sqrtf(omu);
    
    float tpv = TAU * v;
    float tpw = TAU * w;
    
    Quaternion out = {
        .x = sqmu * sinf(tpv),
        .y = sqmu * cosf(tpv),
        .z = squ * sinf(tpw),
        .w = squ * cosf(tpw)
    };
    
    return out;
}





// Operations


Quaternion quaternion_add(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_sub(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_mul(
    const Quaternion* q0,
    const Quaternion* q1
) {
    Quaternion out = {
        q0->w * q1->x + q0->x * q1->w + q0->y * q1->z - q0->z * q1->y,
        q0->w * q1->y - q0->x * q1->z + q0->y * q1->w + q0->z * q1->x,
        q0->w * q1->z + q0->x * q1->y - q0->y * q1->x + q0->z * q1->w,
        q0->w * q1->w - q0->x * q1->x - q0->y * q1->y - q0->z * q1->z
    };
    
    return out;
}

Quaternion quaternion_div(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_unm(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_pow(
    const Quaternion* q0,
    const float pow
) {
    
}


int quaternion_lt(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


int quaternion_le(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


int quaternion_eq(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_scale(
    const Quaternion* q0,
    const float scale
) {
    
}


Quaternion quaternion_mul_matrix_l(
    const Quaternion* q0,
    const Matrix* matrix
) {
    
}


Quaternion quaternion_mul_matrix_r(
    const Matrix* matrix,
    const Quaternion* q0
) {
    
}


Vector3 quaternion_rotate_vector(
    const Quaternion* q0,
    const Vector3* vector
) {
    
}


Quaternion quaternion_combine_imaginary(
    const Quaternion* q0,
    const Vector3* vector
) {
    
}


Quaternion quaternion_scale_inv(
    const Quaternion* q0,
    const float scale
) {
    
}





// Methods


Quaternion quaternion_unit(
    const Quaternion* q0
) {
    
}


float quaternion_length(
    const Quaternion* q0
) {
    
}


float quaternion_length_acc(
    const Quaternion* q0
) {
    
}


float quaternion_length_squared(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_exp(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_exp_map(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_exp_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_log(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_log_map(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_log_map_sym(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


float quaternion_hypot(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_normalize(
    const Quaternion* q0
) {
    
}


int quaternion_is_unit(
    const Quaternion* q0
) {
    
}


float quaternion_dot(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_conjugate(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_inverse(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_negate(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_difference(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


float quaternion_distance(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


float quaternion_distance_sym(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


float quaternion_distance_chord(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


float quaternion_distance_abs(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


Quaternion quaternion_slerp(
    const Quaternion* q0,
    const Quaternion* q1,
    const float alpha
) {
    
}


Quaternion quaternion_slerp_identity(
    const Quaternion* q1,
    const float alpha
) {
    
}


void quaternion_slerp_function_init(
    const Quaternion* q0,
    const Quaternion* q1,
    struct SlerpState* out_slerp_state
) {
    
}


Quaternion quaternion_slerp_function(
    const struct SlerpState* slerp_state,
    const float alpha
) {
    
}


size_t quaternion_get_intermediates_count(
    const size_t number,
    const int include_endpoints
) {
    
}


void quaternion_intermediates(
    const Quaternion* q0,
    const Quaternion* q1,
    const size_t number,
    const int include_endpoints,
    Quaternion out_intermediates[]
) {
    
}


Quaternion quaternion_derivative(
    const Quaternion* q0,
    const Vector3* rate
) {
    
}


Quaternion quaternion_integrate(
    const Quaternion* q0,
    const Vector3* rate,
    const float timestep
) {
    
}


Quaternion quaternion_angular_velocity(
    const Quaternion* q0,
    const Quaternion* q1,
    const float timestep
) {
    
}


Quaternion quaternion_minimal_rotation(
    const Quaternion* q0,
    const Quaternion* q1
) {
    
}


int quaternion_approx_eq(
    const Quaternion* q0,
    const Quaternion* q1,
    const float epsilon
) {
    
}


int quaternion_is_nan(
    const Quaternion* q0
) {
    
}





// Deconstructors


void quaternion_to_matrix(
    const Quaternion* q0,
    const Vector3* position, //optional
    Matrix* out
) {
    
}


void quaternion_to_matrix_vectors(
    const Quaternion* q0,
    Vector3* out_vx,
    Vector3* out_vy,
    Vector3* out_vz
) {
    
}


float quaternion_to_axis_angle(
    const Quaternion* q0,
    Vector3* out_axis
) {
    
}


Vector3 quaternion_to_euler_vector(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_xyz(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_xzy(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_yxz(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_yzx(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_zxy(
    const Quaternion* q0
) {
    
}


EulerAngles quaternion_to_euler_angles_zyx(
    const Quaternion* q0
) {
    
}


Vector3 quaternion_vector(
    const Quaternion* q0
) {
    
}


float quaternion_scalar(
    const Quaternion* q0
) {
    
}


Quaternion quaternion_imaginary(
    const Quaternion* q0
) {
    
}


#define QUATERNION_NULL "NULL"
#define QUATERNION_NULL_SIZE sizeof(QUATERNION_NULL)
#define MAXIMUM_DECIMAL_PLACES 20
#define QUATERNION_FORMAT_STRING_G "%.*g, %.*g, %.*g, %.*g"
#define QUATERNION_FORMAT_STRING_F "%.*f, %.*f, %.*f, %.*f"
#define QUATERNION_STRING_LENGTH (sizeof(QUATERNION_FORMAT_STRING_G) - (4 * 1))

char* quaternion_to_string(
    const Quaternion* q0,
    const unsigned int decimal_places,
    const char formatter
) {
    if (!q0) {
        char* null_string = malloc(QUATERNION_NULL_SIZE);
        if (!null_string) {
            return NULL;
        };
        snprintf(null_string, QUATERNION_NULL_SIZE, QUATERNION_NULL);
        return null_string;
    }
    
    const unsigned int f_decimal_places = uint_min(
        decimal_places, MAXIMUM_DECIMAL_PLACES
    );
    
    const size_t buffer_size = 
        QUATERNION_STRING_LENGTH + f_decimal_places * 4;
    
    char* buffer = (char*) malloc(buffer_size);
    if (!buffer) {
        return NULL;
    }
    
    const char* format_string = formatter == 'f'
        ? QUATERNION_FORMAT_STRING_F
        : QUATERNION_FORMAT_STRING_G;
    
    int write_size = snprintf(
        buffer, buffer_size, format_string,
        f_decimal_places, q0->x, 
        f_decimal_places, q0->y, 
        f_decimal_places, q0->z, 
        f_decimal_places, q0->w
    );
    
    if (write_size < 0) {
        free(buffer);
        return NULL;
    }
    
    if (write_size < buffer_size) {
        return buffer;
    }
    
    char* resized_buffer = realloc((void*) buffer, write_size + 1);
    if (!resized_buffer) {
        free(buffer);
        return NULL;
    }
    buffer = resized_buffer;
    
    int rewrite_size = snprintf(
        buffer, write_size + 1, format_string,
        f_decimal_places, q0->x, 
        f_decimal_places, q0->y, 
        f_decimal_places, q0->z, 
        f_decimal_places, q0->w
    );
    
    if ((rewrite_size < 0) || (rewrite_size >= (write_size + 1))) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}

