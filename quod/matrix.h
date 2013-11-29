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

#include "globals.h"

void glSetPerspective(float* matrix,
                      float fovyInDegrees, float aspectRatio,
                      float znear, float zfar);
void glSetFrustum(float* matrix,
                  float left, float right, float bottom, float top,
                  float znear, float zfar);

void matrix_print_row_major(float* matrix, size_t size);
void matrix_print_col_major(float* matrix, size_t size);

void matrix_transpose_square(float* dst, float* src, size_t size);
void matrix_translate_to_position(float* dst, float* src, point3f* pos);
#endif
