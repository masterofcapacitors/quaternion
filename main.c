#include "c/f32/quaternion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void print_quaternion(const Quaternion* q0, unsigned int decimal_places) {
    char* q0_str = quaternion_to_string(q0, decimal_places, 'f');
    if (q0_str) {
        printf("%s\n", q0_str);
        free(q0_str);
    } else {
        printf("Failed to convert to string\n");
    }
}

//static const float NaN = 0.0f / 0.0f;
//static const float POS_INF = 1.0f / 0.0f;
//static const float NEG_INF = -1.0f / 0.0f;

int main(int argc, char** argv) {
    Quaternion q0 = quaternion_random(&random_float);
    Quaternion q1 = quaternion_random(&random_float);
    Quaternion q2 = quaternion_mul(&q0, &q1);
    
    print_quaternion(&q2, 6);
    
    /* 
    Quaternion test_cases[] = {
        quaternion_new(0, 0, 0, 1),
        quaternion_new(-0.5, -0.5, -0.5, -0.5),
        quaternion_new(NaN, NaN, NaN, NaN),
        quaternion_new(POS_INF, NEG_INF, POS_INF, NEG_INF),
        quaternion_new(100.0f, 100.0f, 100.0f, 100.0f),
        quaternion_new(
            -529087.903752390, -529087.903752390, 
            -529087.903752390, -529087.903752390
            ),
        quaternion_new(0.123456789, -0.987654321, 1.0, -1.0),
        quaternion_new(1e-10, -1e-10, 1e-20, -1e-20)
    };
    
    size_t tests = sizeof(test_cases) / sizeof(Quaternion);
    for (int i = 0; i < tests; i++) {
        print_quaternion(&(test_cases[i]), 6);
    }
    
    print_quaternion(NULL, 6);
    */
    
}

/*

-0.5, -0.5, -0.5, -0.5
0.5, 0.5, 0.5, 0.5
NaN, NaN, NaN, NaN
NaN, 0.5, 0.5, 0.5
0.5, NaN, NaN, 0.5
0.5, 0.5, 0.5, NaN
inf, inf, inf, inf
inf, 0.5, 0.5, 0.5
0.5, inf, inf, 0.5
0.5, 0.5, 0.5, inf
-inf, -inf, -inf, -inf
-inf, 0.5, 0.5, 0.5
0.5, -inf, -inf, 0.5
0.5, 0.5, 0.5, -inf
100.0, 100.0, 100.0, 100.0
-529087.903752390, -529087.903752390, -529087.903752390, -529087.903752390
0.0, 0.0, 0.0, 0.0
-0.0, -0.0, -0.0, -0.0
-1.0, 0.0, 1.0, -1.0
0.0, -1.0, 0.5, 100.0
1e-10, -1e-10, 1e-20, -1e-20
0.123456789, -0.987654321, 1.0, -1.0

*/