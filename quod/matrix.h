//
//  matrix.h
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_MATRIX_H
#define QUOD_MATRIX_H

#include <stdlib.h>
#include "vector.h"

typedef struct vector3f vector3f; // avoid circullar dependencies

float* matrix_perspective_new(float fovyInDegrees, float aspectRatio,
                              float znear, float zfar);
void glSetFrustum(float* matrix,
                  float left,  float right,
                  float bottom, float top,
                  float znear, float zfar);
float* matrix_view_new(vector3f* dir, const vector3f* up);

float* matrix_translation_new(float x, float y, float z);
float* matrix_identity_new();

void matrix_print_row_major(const float* matrix, size_t size);
void matrix_print_col_major(const float* matrix, size_t size);

void matrix_transpose_square(float* dst, const float* src, size_t size);
void matrix_translate_to_position(float* dst, const float* src, const vector3f* vec);

void matrix_multiplication(float* matrix, const float* a, const float* b);

int matrix_inverse(float* matrix, const float* a);

float matrix3f_det(const float* matrix);
float matrix4f_det(const float* matrix);

#endif
