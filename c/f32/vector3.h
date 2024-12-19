#ifndef VECTOR3_H
#define VECTOR3_H

#include "types.h"

extern const Vector3 VECTOR3_ZERO;
extern const Vector3 VECTOR3_ONE;
extern const Vector3 VECTOR3_X_AXIS;
extern const Vector3 VECTOR3_Y_AXIS;
extern const Vector3 VECTOR3_Z_AXIS;
extern const Vector3 VECTOR3_XY_AXIS;
extern const Vector3 VECTOR3_YZ_AXIS;
extern const Vector3 VECTOR3_XZ_AXIS;

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


Vector3 vector3_mul(
    const Vector3* vector,
    float scalar
);

Vector3 vector3_div(
    const Vector3* vector,
    float scalar
);


#endif
