#ifndef TYPES_H
#define TYPES_H

typedef struct Quaternion {
    const float x, y, z, w;
} Quaternion;

typedef struct EulerAngles {
    const float x, y, z;
} EulerAngles;

typedef struct Vector3 {
    float x, y, z;
} Vector3;

typedef struct Matrix {
    float r00, r01, r02, tx,
          r10, r11, r12, ty,
          r20, r21, r22, tz,
           h1,  h2,  h3, h4;
} Matrix;

#endif
