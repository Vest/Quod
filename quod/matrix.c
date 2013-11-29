//
//  matrix.c
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//  Perspective code taken from http://www.opengl.org/wiki/GluPerspective_code

#include <math.h>
#include <stdio.h>
#include "matrix.h"

void glSetPerspective(float* matrix,
                      float fovyInDegrees, float aspectRatio,
                      float znear, float zfar) {
    float ymax, xmax;
    // float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    //ymin = -ymax;
    //xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glSetFrustum(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void glSetFrustum(float* matrix,
                  float left, float right, float bottom, float top,
                  float znear, float zfar) {
    float temp, temp2, temp3, temp4;
    
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}

void matrix_print_row_major(float* matrix, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            printf("%lf ", matrix[i * size + j]);
        printf("\n");
    }
}

void matrix_print_col_major(float* matrix, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++)
            printf("%lf ", matrix[i * size + j]);
        printf("\n");
    }
}

void matrix_transpose_square(float* dst, float* src, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            dst[j * size + i] = src[i * size + j];
}

void matrix_translate_to_position(float* dst, float* src, point3f* pos) {
    size_t i;
    
    for (i = 0; i < 16; i++)
        dst[i] = src[i];
    
    dst[3]  = -pos->x;
    dst[7]  = -pos->y;
    dst[11] = -pos->z;
}