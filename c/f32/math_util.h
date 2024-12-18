#ifndef MATH_UTIL_H
#define MATH_UTIL_H

static inline unsigned int uint_min(unsigned int a, unsigned int b) {
    return (a < b) ? a : b;
}

static inline unsigned int uint_max(unsigned int a, unsigned int b) {
    return (a > b) ? a : b;
}


#ifdef M_DEFINE_CONSTANTS
    #define PI  3.14159265358979323846
    #define TAU 6.28318530717958647692
#endif

#endif
