#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f32/quaternion.h"
#include "f32/vector3.h"



void print_quaternion(const Quaternion* q0, unsigned int decimal_places) {
    char* q0_str = quaternion_to_string(q0, decimal_places, 'f');
    if (q0_str) {
        printf("%s\n", q0_str);
        free(q0_str);
    } else {
        printf("Failed to convert to string\n");
    }
}

// Turn into "//*" to remove comment
/*
static const float NaN = 0.0f / 0.0f;
static const float POS_INF = 1.0f / 0.0f;
static const float NEG_INF = -1.0f / 0.0f;

void run_test_cases() {
    const unsigned int decimal_places = 1;
    
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
        print_quaternion(&(test_cases[i]), decimal_places);
    }
    
    print_quaternion(NULL, decimal_places);
}
/**/

int main() { //int argc, char** argv) {
    Vector3 axis = vector3_new(0, 0, 1);
    const float angle = 30.0f;
    
    Quaternion faa = quaternion_from_axis_angle(&axis, angle);
    Quaternion fa2 = quaternion_from_axis_angle(&VECTOR3_Y_AXIS, angle);
    
    print_quaternion(&faa, 7);
    print_quaternion(&fa2, 6);
    
    fa2 = faa;
    
    
    
    
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