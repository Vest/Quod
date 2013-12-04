//
//  matrix.c
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//  Perspective code adopted from http://www.opengl.org/wiki/GluPerspective_code
//  Matrix from direction implementation borrowed from http://wiki.delphigl.com/index.php/gluLookAt

#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "globals.h"

float* matrix_perspective_new(float fovyInDegrees, float aspectRatio,
                              float znear, float zfar) {
    float *r = malloc(sizeof(float) * 16);
    float ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    float xmax = ymax * aspectRatio;
    
    glSetFrustum(r, -xmax, xmax, -ymax, ymax, znear, zfar);
    
    return r;
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

float* matrix_view_new(vector3f* dir, const vector3f* up) {
    float *r = malloc(sizeof(float) * 16);
    
    vector3f s;
    vector3f_normalize(dir);
    vector3f_cross_product(&s, dir, up);
    vector3f_normalize(&s);
    
	vector3f u;
    vector3f_cross_product(&u, &s, dir);
	vector3f_normalize(&u);
    
    r[0]  = s.x;     r[1]  = s.y;     r[2]  = s.z;     r[3] = 0.0f;
    r[4]  = u.x;     r[5]  = u.y;     r[6]  = u.z;     r[7] = 0.0f;
    r[8]  = -dir->x; r[9]  = -dir->y; r[10] = -dir->z; r[11] = 0.0f;
    r[12] = 0.0f;    r[13] = 0.0f;    r[14] = 0.0f;    r[15] = 1.0f;
    
    return r;
}

float* matrix_translation_new(float x, float y, float z) {
    float *r = malloc(sizeof(float) * 16);
    
    r[0] = r[5] = r[10] = r[15] = 1.0f;
    r[1] = r[2] = r[4] = r[6] = r[8] = r[9] = r[12] = r[13] = r[14] = 0.0f;
    r[3] = x;
    r[7] = y;
    r[11] = z;
    
    return r;
}

float* matrix_identity_new() {
    float *r = malloc(sizeof(float) * 16);
    
    r[0] = r[5] = r[10] = r[15] = 1.0f;
    r[1] = r[2] = r[3] = r[4] = r[6] = r[7] = r[8] = r[9] = r[11] = r[12] = r[13] = r[14] = 0.0f;
    
    return r;
}

void matrix_print_row_major(const float* matrix, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            printf("%lf ", matrix[i * size + j]);
        printf("\n");
    }
}

void matrix_print_col_major(const float* matrix, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++)
            printf("%lf ", matrix[i * size + j]);
        printf("\n");
    }
}

void matrix_transpose_square(float* dst, const float* src, size_t size) {
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            dst[j * size + i] = src[i * size + j];
}

void matrix_translate_to_position(float* dst, const float* src, const vector3f* vec) {
    size_t i;
    
    for (i = 0; i < 16; i++)
        dst[i] = src[i];
    
    dst[3]  = -vec->x;
    dst[7]  = -vec->y;
    dst[11] = -vec->z;
}

void matrix_multiplication(float* matrix, const float* a, const float* b) {
/*
    matrix_print_row_major(a, 4);
    matrix_print_row_major(b, 4);
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            float n = 0;
            for (int k = 0; k < 4; k++) {
                printf("(%f * %f = %f )", a[k * 4 + j], b[i * 4 + k], b[i * 4 + k] * a[k * 4 + j]);
                n += b[i + k * 4] * a[k + j * 4];
            }
            matrix[i * 4 + j] = n;
            printf("\n");
        }
    return;
*/
    
    //  matrix_print_row_major(a, 4);
    //  matrix_print_row_major(b, 4);
    //  exit(1);
    
    // Row 1
    matrix[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8]  + a[3] * b[12];   // Column 1
    matrix[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9]  + a[3] * b[13];   // Column 2
    matrix[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];   // Column 3
    matrix[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];   // Column 4
    
    // Row 2
    matrix[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8]  + a[7] * b[12];   // Column 1
    matrix[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9]  + a[7] * b[13];   // Column 2
    matrix[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];   // Column 3
    matrix[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];   // Column 4
    
    // Row 3
    matrix[8]  = a[8] * b[0] + a[9] * b[4] + a[10] * b[8]  + a[11] * b[12]; // Column 1
    matrix[9]  = a[8] * b[1] + a[9] * b[5] + a[10] * b[9]  + a[11] * b[13]; // Column 2
    matrix[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14]; // Column 3
    matrix[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15]; // Column 4
    
    // Row 4
    matrix[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8]  + a[15] * b[12]; // Column 1
    matrix[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9]  + a[15] * b[13]; // Column 2
    matrix[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14]; // Column 3
    matrix[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]; // Column 4
}

/* hidden method */
float* matrix4f_submatrix(const float* matrix, int i, int j) {
    int ti, tj, idst, jdst;
    float* r = (float*)malloc(sizeof(float) * 9);
    
    for (ti = 0; ti < 4; ti++) {
        if (ti < i)
            idst = ti;
        else if (ti > i)
            idst = ti - 1;
        
        for (tj = 0; tj < 4; tj++) {
            if (tj < j)
                jdst = tj;
            else if (tj > j)
                jdst = tj -1 ;
            
            if (ti != i && tj != j)
                r[idst * 3 + jdst] = matrix[ti * 4 + tj];
        }
    }
    
    return r;
}

int matrix_inverse(float* matrix, const float* a) {
    float  det = matrix4f_det(a);
    float* m3fTemp;
    int     i, j, sign;
    
    if (fabs(det) < EPSILON)
        return 0;
    
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            sign = 1 - ((i + j) % 2 ) * 2;
            
            m3fTemp = matrix4f_submatrix(a, i, j );
            
            matrix[i + j * 4] = (matrix3f_det(m3fTemp) * sign ) / det;
        
            free(m3fTemp);
        }
    
    return 1;
}

float matrix4f_det(const float* matrix) {
    float det = 0.0f;
    float result = 0.0f;
    int i = 1;
    
    float* mSub3f = NULL;
    int     n;
    
    for (n = 0; n < 4; n++, i *= -1) {
        mSub3f = matrix4f_submatrix(matrix, 0, n);
        
        det     = matrix3f_det(mSub3f);
        result += matrix[n] * det * i;
    }
    
    return result;
}

float matrix3f_det(const float* matrix) {
    float det;
    
    det = matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5]) -
          matrix[1] * (matrix[3] * matrix[8] - matrix[6] * matrix[5]) +
          matrix[2] * (matrix[3] * matrix[7] - matrix[6] * matrix[4]);
    
    return det;
}