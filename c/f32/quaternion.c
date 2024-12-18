#include "quaternion.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_DEFINE_CONSTANTS
#include "math_util.h"

Quaternion quaternion_new(float x, float y, float z, float w) {
    Quaternion q0 = { x, y, z, w };
    return q0;
}

// Assumes srand() has been called at least once.
// Not thread safe or reentrant since it relies on `rand()`.
float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

// Uses `rand_r()`. Assumes `void* seed` is castable to `unsigned int*`.
float random_float_r(void* seed) {
    return (float)rand() / (float)RAND_MAX;
    //return (float)rand_r(*((unsigned int*)seed)) / (float)RAND_MAX;
}

Quaternion quaternion_random(float (*random_float_generator)()) {
    float u = random_float_generator();
    float v = random_float_generator();
    float w = random_float_generator();
    
    float omu = 1.0f - u;
    float squ = sqrtf(u);
    float sqmu = sqrtf(omu);
    
    float tpv = TAU * v;
    float tpw = TAU * w;
    
    Quaternion out = {
        .x = sqmu * sinf(tpv),
        .y = sqmu * cosf(tpv),
        .z = squ * sinf(tpw),
        .w = squ * cosf(tpw)
    };
    
    return out;
}

// Will call the random_float_generator 3 times.
Quaternion quaternion_random_state(
    float (*random_float_generator)(void*), 
    void* state
) {
    float u = random_float_generator(state);
    float v = random_float_generator(state);
    float w = random_float_generator(state);
    
    float omu = 1.0f - u;
    float squ = sqrtf(u);
    float sqmu = sqrtf(omu);
    
    float tpv = TAU * v;
    float tpw = TAU * w;
    
    Quaternion out = {
        .x = sqmu * sinf(tpv),
        .y = sqmu * cosf(tpv),
        .z = squ * sinf(tpw),
        .w = squ * cosf(tpw)
    };
    
    return out;
}


#define QUATERNION_NULL "NULL"
#define QUATERNION_NULL_SIZE sizeof(QUATERNION_NULL)
#define MAXIMUM_DECIMAL_PLACES 20
#define QUATERNION_FORMAT_STRING_G "%.*g, %.*g, %.*g, %.*g"
#define QUATERNION_FORMAT_STRING_F "%.*f, %.*f, %.*f, %.*f"
#define QUATERNION_STRING_LENGTH (sizeof(QUATERNION_FORMAT_STRING_G))

char* quaternion_to_string(
    const Quaternion* q0,
    const unsigned int decimal_places,
    const char formatter
) {
    if (!q0) {
        char* null_string = malloc(QUATERNION_NULL_SIZE);
        if (!null_string) {
            return NULL;
        };
        snprintf(null_string, QUATERNION_NULL_SIZE, QUATERNION_NULL);
        return null_string;
    }
    
    const unsigned int f_decimal_places = uint_min(
        decimal_places, MAXIMUM_DECIMAL_PLACES
    );
    
    const size_t buffer_size = 
        QUATERNION_STRING_LENGTH + f_decimal_places * 4;
    
    char* buffer = (char*) malloc(buffer_size);
    if (!buffer) {
        return NULL;
    }
    
    const char* format_string = formatter == 'g'
        ? QUATERNION_FORMAT_STRING_G
        : QUATERNION_FORMAT_STRING_F;
    
    int write_size = snprintf(
        buffer, buffer_size, format_string,
        f_decimal_places, q0->x, 
        f_decimal_places, q0->y, 
        f_decimal_places, q0->z, 
        f_decimal_places, q0->w
    );
    
    if (write_size < 0) {
        free(buffer);
        return NULL;
    }
    
    if (write_size < buffer_size) {
        printf("fits\n");
        return buffer;
    }
    
    char* resized_buffer = realloc((void*) buffer, write_size + 1);
    if (!resized_buffer) {
        free(buffer);
        return NULL;
    }
    buffer = resized_buffer;
    
    int rewrite_size = snprintf(
        buffer, write_size + 1, format_string,
        f_decimal_places, q0->x, 
        f_decimal_places, q0->y, 
        f_decimal_places, q0->z, 
        f_decimal_places, q0->w
    );
    
    if ((rewrite_size < 0) || (rewrite_size >= (write_size + 1))) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}
