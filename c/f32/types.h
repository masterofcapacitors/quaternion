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

typedef struct ALIGN(16) Matrix {
    float matrix[4][4];
} Matrix;

#endif
