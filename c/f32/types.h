#ifndef TYPES_H
#define TYPES_H

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

typedef struct EulerAngles {
    float x, y, z;
} EulerAngles;

typedef struct Vector3 {
    float x, y, z;
} Vector3;

typedef struct Matrix {
    float matrix[4][4];
} Matrix;

#endif
