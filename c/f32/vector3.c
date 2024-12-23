#include "vector3.h"

#include <math.h>


float vector3_magnitude(
    const Vector3* vector
) {
    const float vx = vector->x;
    const float vy = vector->y;
    const float vz = vector->z;
    
    return sqrtf(vx * vx + vy * vy + vz * vz);
}


Vector3 vector3_unit(
    const Vector3* vector
) {
    return vector3_div(vector, vector3_magnitude(vector));
}

Vector3 vector3_unit_default(
    const Vector3* vector,
    const float epsilon,
    const Vector3* default_vector
) {
    float magnitude = vector3_magnitude(vector);
    if (magnitude >= epsilon) {
        return vector3_div(vector, magnitude);
    }
    
    return *default_vector;
}


Vector3 vector3_mul(
    const Vector3* vector,
    float scalar
) {
    Vector3 out = {
        .x = vector->x * scalar,
        .y = vector->y * scalar,
        .z = vector->z * scalar
    };
    
    return out;
}


Vector3 vector3_div(
    const Vector3* vector,
    float scalar
) {
    Vector3 out = {
        .x = vector->x / scalar,
        .y = vector->y / scalar,
        .z = vector->z / scalar
    };
    
    return out;
}

