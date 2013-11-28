//
//  quaternion.c
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013
//  http://rosettacode.org/wiki/Simple_Quaternion_type_and_operations#C
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "quaternion.h"

quaternion_t *quaternion_new(void)
{
    return malloc(sizeof(quaternion_t));
}

quaternion_t *quaternion_new_set(double q1,
                                 double q2,
                                 double q3,
                                 double q4)
{
    quaternion_t *q = malloc(sizeof(quaternion_t));
    if (q != NULL) {
        q->q[0] = q1; q->q[1] = q2; q->q[2] = q3; q->q[3] = q4;
    }
    return q;
}


void quaternion_copy(quaternion_t *r, quaternion_t *q)
{
    size_t i;
    
    if (r == NULL || q == NULL) return;
    for(i = 0; i < 4; i++) r->q[i] = q->q[i];
}


double quaternion_norm(quaternion_t *q)
{
    size_t i;
    double r = 0.0;
    
    if (q == NULL) {
        fprintf(stderr, "NULL quaternion in norm\n");
        return 0.0;
    }
    
    for(i = 0; i < 4; i++) r += q->q[i] * q->q[i];
    return sqrt(r);
}


void quaternion_neg(quaternion_t *r, quaternion_t *q)
{
    size_t i;
    
    if (q == NULL || r == NULL) return;
    for(i = 0; i < 4; i++) r->q[i] = -q->q[i];
}


void quaternion_conj(quaternion_t *r, quaternion_t *q)
{
    size_t i;
    
    if (q == NULL || r == NULL) return;
    r->q[0] = q->q[0];
    for(i = 1; i < 4; i++) r->q[i] = -q->q[i];
}


void quaternion_add_d(quaternion_t *r, quaternion_t *q, double d)
{
    if (q == NULL || r == NULL) return;
    quaternion_copy(r, q);
    r->q[0] += d;
}


void quaternion_add(quaternion_t *r, quaternion_t *a, quaternion_t *b)
{
    size_t i;
    
    if (r == NULL || a == NULL || b == NULL) return;
    for(i = 0; i < 4; i++) r->q[i] = a->q[i] + b->q[i];
}


void quaternion_mul_d(quaternion_t *r, quaternion_t *q, double d)
{
    size_t i;
    
    if (r == NULL || q == NULL) return;
    for(i = 0; i < 4; i++) r->q[i] = q->q[i] * d;
}

int quaternion_equal(quaternion_t *a, quaternion_t *b)
{
    size_t i;
    
    for(i = 0; i < 4; i++) if (a->q[i] != b->q[i]) return 0;
    return 1;
}


#define A(N) (a->q[(N)])
#define B(N) (b->q[(N)])
#define R(N) (r->q[(N)])
void quaternion_mul(quaternion_t *r, quaternion_t *a, quaternion_t *b)
{
    // size_t i;
    // double ri = 0.0;
    
    if (r == NULL || a == NULL || b == NULL) return;
    R(0) = A(0)*B(0) - A(1)*B(1) - A(2)*B(2) - A(3)*B(3);
    R(1) = A(0)*B(1) + A(1)*B(0) + A(2)*B(3) - A(3)*B(2);
    R(2) = A(0)*B(2) - A(1)*B(3) + A(2)*B(0) + A(3)*B(1);
    R(3) = A(0)*B(3) + A(1)*B(2) - A(2)*B(1) + A(3)*B(0);
}
#undef A
#undef B
#undef R


void quaternion_print(quaternion_t *q)
{
    if (q == NULL) return;
    printf("(%lf, %lf, %lf, %lf)\n",
           q->q[0], q->q[1], q->q[2], q->q[3]);
}

void quaternion_to_rotation_matrix(quaternion_t* q, float* matrix) {
    float xx = q->q[0] * q->q[0];
    float xy = q->q[0] * q->q[1];
    float xz = q->q[0] * q->q[2];
    float xw = q->q[0] * q->q[3];
    
    float yy = q->q[1] * q->q[1];
    float yz = q->q[1] * q->q[2];
    float yw = q->q[1] * q->q[3];
    
    float zz = q->q[2] * q->q[2];
    float zw = q->q[2] * q->q[3];
    
    matrix[0]  = 1 - 2 * ( yy + zz );
    matrix[1]  =     2 * ( xy - zw );
    matrix[2]  =     2 * ( xz + yw );
    
    matrix[4]  =     2 * ( xy + zw );
    matrix[5]  = 1 - 2 * ( xx + zz );
    matrix[6]  =     2 * ( yz - xw );
    
    matrix[8]  =     2 * ( xz - yw );
    matrix[9]  =     2 * ( yz + xw );
    matrix[10] = 1 - 2 * ( xx + yy );
    
    matrix[3]  = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}