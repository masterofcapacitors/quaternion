#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"

// define `ML_LEFT_HANDED` to specify left-handedness in matrix.
// Default is right handedness.
// define `ML_Y_UPVECTOR`

static inline void matrix_with_default_pos(
    Matrix* matrix
) {
    matrix->matrix[0][3] = 0.0f;
    matrix->matrix[1][3] = 0.0f;
    matrix->matrix[2][3] = 0.0f;
};

static inline void matrix_with_posf(
    Matrix* matrix,
    float x, float y, float z
) {
    matrix->matrix[0][3] = x;
    matrix->matrix[1][3] = y;
    matrix->matrix[2][3] = z;
};

static inline void matrix_with_posv(
    Matrix* matrix,
    Vector3* position
) {
    matrix->matrix[0][3] = position->x;
    matrix->matrix[1][3] = position->y;
    matrix->matrix[2][3] = position->z;
};

// Initialize a matrix with default rotation
// Does NOT initialize positions or the homogenous row.
static inline void matrix_with_default_rotation(
    Matrix* matrix
) {
    matrix->matrix[0][0] = 1.0f;
    matrix->matrix[0][1] = 0.0f;
    matrix->matrix[0][2] = 0.0f;
    matrix->matrix[1][0] = 0.0f;
    matrix->matrix[1][1] = 1.0f;
    matrix->matrix[1][2] = 0.0f;
    matrix->matrix[2][0] = 0.0f;
    matrix->matrix[2][1] = 0.0f;
    #ifdef ML_LEFT_HANDED
        matrix->matrix[2][2] = -1.0f;
    #else
        matrix->matrix[2][2] = 1.0f;
    #endif
}

static inline void matrix_with_components(
    Matrix* matrix,
    float r00, float r01, float r02,
    float r10, float r11, float r12,
    float r20, float r21, float r22
) {
    matrix->matrix[0][0] = r00;
    matrix->matrix[0][1] = r01;
    matrix->matrix[0][2] = r02;
    matrix->matrix[1][0] = r10;
    matrix->matrix[1][1] = r11;
    matrix->matrix[1][2] = r12;
    matrix->matrix[2][0] = r20;
    matrix->matrix[2][1] = r21;
    matrix->matrix[2][2] = r22;
};

static inline void matrix_with_vectors(
    Matrix* matrix,
    Vector3* right_vector,
    Vector3* up_vector,
    Vector3* look_vector
) {
    matrix->matrix[0][0] = right_vector->x;
    matrix->matrix[0][1] = right_vector->y;
    matrix->matrix[0][2] = right_vector->z;
    
    matrix->matrix[1][0] = up_vector->x;
    matrix->matrix[1][1] = up_vector->y;
    matrix->matrix[1][2] = up_vector->z;
    
    #ifdef ML_LEFT_HANDED
        matrix->matrix[2][0] = -look_vector->x;
        matrix->matrix[2][1] = -look_vector->y;
        matrix->matrix[2][2] = -look_vector->z;
    #else
        matrix->matrix[2][0] = look_vector->x;
        matrix->matrix[2][1] = look_vector->y;
        matrix->matrix[2][2] = look_vector->z;
    #endif
}

void matrix_with_quaternion(
    Matrix* matrix,
    Quaternion* quaternion
);

static inline void matrix_with_homogenous_row(
    Matrix* matrix
) {
    matrix->matrix[3][0] = 0;
    matrix->matrix[3][1] = 0;
    matrix->matrix[3][2] = 0;
    matrix->matrix[3][3] = 1;
}


static inline void matrix_from_posf(
    float x, float y, float z
) {
    Matrix matrix;
    matrix_with_posf(&matrix, x, y, z);
    matrix_with_default_rotation(&matrix);
    matrix_with_homogenous_row(&matrix);
    return matrix;
}

void matrix_from_components(
    float r00, float r01, float r02,
    float r10, float r11, float r12,
    float r20, float r21, float r22
);

void matrix_from_components_posv(
    Vector3* position,
    float r00, float r01, float r02,
    float r10, float r11, float r12,
    float r20, float r21, float r22
);

void matrix_from_components_posf(
    float x, float y, float z,
    float r00, float r01, float r02,
    float r10, float r11, float r12,
    float r20, float r21, float r22
);

void matrix_from_vectors(
    Vector3* lookVector,
    Vector3* rightVector,
    Vector3* upVector
);

void matrix_from_vectors_pos(
    Vector3* position,
    Vector3* lookVector,
    Vector3* rightVector,
    Vector3* upVector
);

void matrix_from_vectors_posf(
    float x, float y, float z,
    Vector3* lookVector,
    Vector3* rightVector,
    Vector3* upVector
);


void matrix_from_quaternion(
    Quaternion* rotation
);

void matrix_from_quaternion_posv(
    Vector3* position,
    Quaternion* rotation
);

void matrix_from_quaternion_posf(
    float x, float y, float z,
    Quaternion* rotation
);

void matrix_from_quaternion_pq(
    float x, float y, float z,
    float q_x, float q_y, float q_z, float q_w
);

void matrix_from_quaternion_posf_aa(
    float x, float y, float z,
    float q_x, float q_y, float q_z, float q_w
);



void matrix_flatten(Matrix* matrix, float out[16]);



#endif
