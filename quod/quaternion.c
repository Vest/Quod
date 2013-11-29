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
#include <math.h>

#include "quaternion.h"

quaternion_t *quaternion_new(void) {
    return malloc(sizeof(quaternion_t));
}

quaternion_t *quaternion_new_set(double w,
                                 double x,
                                 double y,
                                 double z) {
    quaternion_t *q = malloc(sizeof(quaternion_t));
    
    if (q != NULL) {
        q->w = w;
        q->x = x;
        q->y = y;
        q->z = z;
    }
    
    return q;
}

quaternion_t* quaternion_new_axis_angle(double degrees,
                                        double x,
                                        double y,
                                        double z) {
    quaternion_t *q = malloc(sizeof(quaternion_t));
    
    if (q != NULL) {
        double radians = degrees * M_PI / 180.0;
        double result = sin(radians / 2.0);
        
        q->w = cos(radians / 2.0f);
        q->x = x * result;
        q->y = y * result;
        q->z = z * result;
    }
    
    return q;
}

void quaternion_copy(quaternion_t *r, const quaternion_t *q) {
    size_t i;
    
    if (r == NULL || q == NULL)
        return;
    
    for (i = 0; i < 4; i++)
        r->q[i] = q->q[i];
}


double quaternion_norm(quaternion_t *q) {
    size_t i;
    double r = 0.0;
    
    if (q == NULL) {
        fprintf(stderr, "NULL quaternion in norm\n");
        return 0.0;
    }
    
    for (i = 0; i < 4; i++)
        r += q->q[i] * q->q[i];
    
    return sqrt(r);
}

void quaternion_normalize(quaternion_t* q) {
    size_t i;
    double norm = quaternion_norm(q);
    
    if (norm == 0.0)
        return;
    
    for (i = 0; i < 4; i++)
        q->q[i] /= norm;
}

void quaternion_neg(quaternion_t *r, quaternion_t *q) {
    size_t i;
    
    if (q == NULL || r == NULL)
        return;
    
    for (i = 0; i < 4; i++)
        r->q[i] = -q->q[i];
}


void quaternion_conj(quaternion_t *r, quaternion_t *q) {
    size_t i;
    
    if (q == NULL || r == NULL)
        return;
    
    r->q[0] = q->q[0];
    for (i = 1; i < 4; i++)
        r->q[i] = -q->q[i];
}


void quaternion_add_d(quaternion_t *r, const quaternion_t *q, double d) {
    if (r == NULL || q == NULL)
        return;
    quaternion_copy(r, q);
    r->q[0] += d;
}


void quaternion_add(quaternion_t *r, quaternion_t *a, quaternion_t *b) {
    size_t i;
    
    if (r == NULL || a == NULL || b == NULL)
        return;
    
    for (i = 0; i < 4; i++)
        r->q[i] = a->q[i] + b->q[i];
}


void quaternion_mul_d(quaternion_t *r, quaternion_t *q, double d) {
    size_t i;
    
    if (r == NULL || q == NULL)
        return;
    
    for (i = 0; i < 4; i++)
        r->q[i] = q->q[i] * d;
}

int quaternion_equal(quaternion_t *a, quaternion_t *b) {
    size_t i;
    
    if (a == NULL || b == NULL)
        return -1;
    
    for(i = 0; i < 4; i++)
        if (a->q[i] != b->q[i])
            return 0;
    
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
    if (q == NULL)
        return;
    
    printf("(%lf, %lf, %lf, %lf)\n",
           q->q[0], q->q[1], q->q[2], q->q[3]);
}

void quaternion_to_rotation_matrix(float* matrix, quaternion_t* q) {
    float xx = q->x * q->x;
    float xy = q->x * q->y;
    float xz = q->x * q->z;
    float xw = q->x * q->w;
    
    float yy = q->y * q->y;
    float yz = q->y * q->z;
    float yw = q->y * q->w;
    
    float zz = q->z * q->z;
    float zw = q->z * q->w;
    
    matrix[0]  = 1.0f - 2 * ( yy + zz );
    matrix[1]  =        2 * ( xy - zw );
    matrix[2]  =        2 * ( xz + yw );
    
    matrix[4]  =        2 * ( xy + zw );
    matrix[5]  = 1.0f - 2 * ( xx + zz );
    matrix[6]  =        2 * ( yz - xw );
    
    matrix[8]  =        2 * ( xz - yw );
    matrix[9]  =        2 * ( yz + xw );
    matrix[10] = 1.0f - 2 * ( xx + yy );
    
    matrix[3]  = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

// http://wiki.delphigl.com/index.php/gluLookAt
void quaternion_to_view_matrix(float* matrix, quaternion_t* q, quaternion_t* up) {
    quaternion_t s;
    quaternion_mul(&s, q, up);
    quaternion_normalize(&s);
    
	quaternion_t u;
    quaternion_mul(&u, &s, q);
	quaternion_normalize(&u);
    
    matrix[0] = s.x;   matrix[4] = s.y;    matrix[8] = s.z;    matrix[12] = 0.0f;
    matrix[1] = u.x;   matrix[5] = u.y;    matrix[9] = u.z;    matrix[13] = 0.0f;
    matrix[2] = -q->x; matrix[6] = -q->y;  matrix[10] = -q->z; matrix[14] = 0.0f;
    matrix[3] = 0.0f;  matrix[7] = 0.0f;   matrix[11] = 0.0f;  matrix[15] = 1.0f;
    /*
     float m[16] = {
     s.x,    s.y,   s.z, 0.0f,
     u.x,    u.y,   u.z, 0.0f,
     -q->x, -q->y, -q->z, 0.0f,
     0.0f,  0.0f,  0.0f, 1.0f
     };
     */
}

double quaternion_get_deg_angle(const quaternion_t* q) {
    return 360.0 * acos(q->w) / M_PI;
}

double quaternion_get_rad_angle(const quaternion_t* q) {
    return 2.0 * acos(q->w);
}

void quaternion_set_deg_angle(quaternion_t* q, double a) {
    q->w = cos(a * M_PI / 360.0f);
}

void quaternion_set_rad_angle(quaternion_t* q, double a) {
    q->w = cos(a / 2.0);
}