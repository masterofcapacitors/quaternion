#include "quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

const float TAU = 2.0f * M_PI;

const Quaternion quaternion_new(float x, float y, float z, float w) {
    
}



// Assumes srand() has been called at least once
static float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

Quaternion quaternion_random() {
    float u = random_float();
    float v = random_float();
    float w = random_float();
    
    float omu = 1.0f - u;
    float squ = sqrtf(u);
    float sqmu = sqrtf(omu);
    
    float tpv = TAU * v;
    float tpw = TAU * w;
    
    Quaternion out;
    out.x = sqmu * sinf(tpv);
    out.y = sqmu * cosf(tpv);
    out.z = squ * sinf(tpw);
    out.w = squ * cosf(tpw);
    
    return out;
}
