#include "matrix.h"

void matrix_with_quaternion(
    Matrix* matrix,
    Quaternion* quaternion
) {
    float x = quaternion->x;
    float y = quaternion->y;
    float z = quaternion->z;
    float w = quaternion->w;

    // Precompute repeated values
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    // Fill the matrix with the appropriate handedness
    #ifdef HANDNESS_LEFT_HANDED
        matrix->matrix[0][0] = 1.0f - 2.0f * (yy + zz);
        matrix->matrix[0][1] = 2.0f * (xy - wz);
        matrix->matrix[0][2] = 2.0f * (xz + wy);

        matrix->matrix[1][0] = 2.0f * (xy + wz);
        matrix->matrix[1][1] = 1.0f - 2.0f * (xx + zz);
        matrix->matrix[1][2] = 2.0f * (yz - wx);

        matrix->matrix[2][0] = 2.0f * (xz - wy);
        matrix->matrix[2][1] = 2.0f * (yz + wx);
        matrix->matrix[2][2] = 1.0f - 2.0f * (xx + yy);
    #else
        matrix->matrix[0][0] = 1.0f - 2.0f * (yy + zz);
        matrix->matrix[0][1] = 2.0f * (xy + wz);
        matrix->matrix[0][2] = 2.0f * (xz - wy);

        matrix->matrix[1][0] = 2.0f * (xy - wz);
        matrix->matrix[1][1] = 1.0f - 2.0f * (xx + zz);
        matrix->matrix[1][2] = 2.0f * (yz + wx);

        matrix->matrix[2][0] = 2.0f * (xz + wy);
        matrix->matrix[2][1] = 2.0f * (yz - wx);
        matrix->matrix[2][2] = 1.0f - 2.0f * (xx + yy);
    #endif
}