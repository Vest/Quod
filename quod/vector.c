//
//  vector.c
//  quod
//
//  Created by Volodin, Vladislav on 29.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "vector.h"

vector3f* vector3f_new(void) {
    return malloc(sizeof(vector3f));
}

vector3f* vector3f_new_set(double x,
                           double y,
                           double z) {
    vector3f *v = malloc(sizeof(vector3f));
    
    if (v != NULL) {
        v->x = x;
        v->y = y;
        v->z = z;
    }
    
    return v;
}

void vector3f_copy(vector3f* r, const vector3f* v) {
    if (r == NULL || v == NULL)
        return;
    
    r->x = v->x;
    r->y = v->y;
    r->z = v->z;
}

double vector3f_norm(const vector3f* v) {
    double r = 0.0;
    
    if (v == NULL) {
        fprintf(stderr, "NULL vector in norm\n");
        return 0.0;
    }
    
    r = v->x * v->x + v->y * v->y + v->z * v->z;
    
    return sqrt(r);
}

void vector3f_normalize(vector3f* v) {
    double norm = vector3f_norm(v);
    
    if (norm == 0.0)
        return;
    
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
}

void vector3f_neg(vector3f* r, const vector3f* v) {
    if (r == NULL || v == NULL)
        return;
    
    r->x = -v->x;
    r->y = -v->y;
    r->z = -v->z;
}

void vector3f_add(vector3f* r, const vector3f* a, const vector3f* b) {
    if (r == NULL || a == NULL || b == NULL)
        return;
    
    r->x = a->x + b->x;
    r->y = a->y + b->y;
    r->z = a->z + b->z;
}

void vector3f_mul_scalar(vector3f* r, const vector3f* v, double d) {
    if (r == NULL || v == NULL)
        return;
    
    r->x = v->x * d;
    r->y = v->y * d;
    r->z = v->z * d;
}

float vector3f_dot_product(const vector3f* a, const vector3f* b) {
    if (a == NULL || b == NULL)
        return 0.0f;
    
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void vector3f_cross_product(vector3f* r, const vector3f* a, const vector3f* b) {
    if (r == NULL || a == NULL || b == NULL)
        return;
    
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
    r->z = a->x * b->y - a->y * b->x;
}

int  vector3f_equal(const vector3f* a, const vector3f* b) {
    if (a == NULL || b == NULL)
        return -1;
    
    return (a->x == b->x &&
            a->y == b->y &&
            a->z == b->z);
}

void vector3f_print(const vector3f* v) {
    if (v == NULL)
        return;
    
    printf("(%lf, %lf, %lf)\n",
           v->x, v->y, v->z);
}

void vector_to_view_matrix(float* matrix, vector3f* dir, vector3f* up) {
    vector3f s;
    vector3f_cross_product(&s, dir, up);
    vector3f_normalize(&s);
    
	vector3f u;
    vector3f_cross_product(&u, &s, dir);
	vector3f_normalize(&u);
    
    matrix[0] = s.x;   matrix[4] = s.y;    matrix[8] = s.z;    matrix[12] = 0.0f;
    matrix[1] = u.x;   matrix[5] = u.y;    matrix[9] = u.z;    matrix[13] = 0.0f;
    matrix[2] = -dir->x; matrix[6] = -dir->y;  matrix[10] = -dir->z; matrix[14] = 0.0f;
    matrix[3] = 0.0f;  matrix[7] = 0.0f;   matrix[11] = 0.0f;  matrix[15] = 1.0f;
    /*
     float m[16] = {
     s.x,    s.y,   s.z, 0.0f,
     u.x,    u.y,   u.z, 0.0f,
     -dir->x, -dir->y, -dir->z, 0.0f,
     0.0f,  0.0f,  0.0f, 1.0f
     };
     */
}