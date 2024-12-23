#ifndef VECTOR3_H
#define VECTOR3_H

#include "types.h"

static inline Vector3 vector3_new(
    const float x, 
    const float y, 
    const float z
) {
    return (Vector3) {x, y, z};
}

float vector3_magnitude(
    const Vector3* vector
);

Vector3 vector3_unit(
    const Vector3* vector
);

Vector3 vector3_unit_default(
    const Vector3* vector,
    const float epsilon,
    const Vector3* default_vector
);


Vector3 vector3_add(
    const Vector3* v0,
    const Vector3* v1
);

Vector3 vector3_scale(
    const Vector3* vector,
    const float scalar
);

Vector3 vector3_div(
    const Vector3* vector,
    const float scalar
);


#endif
