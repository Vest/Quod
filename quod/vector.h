//
//  vector.h
//  quod
//
//  Created by Volodin, Vladislav on 29.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_VECTOR_H
#define QUOD_VECTOR_H

#include "matrix.h"

typedef struct vector3f {
    float x, y, z;
} vector3f;

vector3f* vector3f_new(void);
vector3f* vector3f_new_set(double x,
                           double y,
                           double z);

void vector3f_copy(vector3f* r, const vector3f* v);

double vector3f_norm(const vector3f* v);
void vector3f_normalize(vector3f* v);

void vector3f_neg(vector3f* r, const vector3f* v);

void vector3f_add(vector3f* r, const vector3f* a, const vector3f* b);

void vector3f_mul_scalar(vector3f* r, const vector3f* v, double d);
float vector3f_dot_product(const vector3f* a, const vector3f* b);
void vector3f_cross_product(vector3f* r, const vector3f* a, const vector3f* b);

int  vector3f_equal(const vector3f* a, const vector3f* b);

void vector3f_print(const vector3f* v);

void vector_mul_matrix(vector3f* r, const vector3f* v, const float* m);

#endif // QUOD_VECTOR_H
