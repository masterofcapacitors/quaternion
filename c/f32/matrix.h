#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    float r00, r01, r02, tx,
          r10, r11, r12, ty,
          r20, r21, r22, tz,
           h1,  h2,  h3, h4;
} Matrix;




#endif
