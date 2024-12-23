#ifndef TYPES_H
#define TYPES_H

#if defined(_MSC_VER) // Microsoft Visual Studio
    #define ALIGN(n) __declspec(align(n))
#elif defined(__GNUC__) || defined(__clang__) // GCC/Clang
    #define ALIGN(n) __attribute__((aligned(n)))
#else
    #define ALIGN(n) // Unsupported compiler: no alignment
    #warning "Alignment directives are not supported on this compiler"
#endif

typedef struct ALIGN(16) Quaternion {
    float x, y, z, w;
} Quaternion;

typedef struct EulerAngles {
    float x, y, z;
} EulerAngles;

typedef struct ALIGN(16) Vector3 {
    float x, y, z;
} Vector3;

static const Vector3 VECTOR3_ZERO    = {0.0f, 0.0f, 0.0f};
static const Vector3 VECTOR3_ONE     = {1.0f, 1.0f, 1.0f};
static const Vector3 VECTOR3_X_AXIS  = {1.0f, 0.0f, 0.0f};
static const Vector3 VECTOR3_Y_AXIS  = {0.0f, 1.0f, 0.0f};
static const Vector3 VECTOR3_Z_AXIS  = {0.0f, 0.0f, 1.0f};
static const Vector3 VECTOR3_XY_AXIS = {1.0f, 1.0f, 0.0f};
static const Vector3 VECTOR3_YZ_AXIS = {0.0f, 1.0f, 1.0f};
static const Vector3 VECTOR3_XZ_AXIS = {1.0f, 0.0f, 1.0f};

typedef struct ALIGN(16) Matrix {
    float matrix[4][4];
} Matrix;

#endif
