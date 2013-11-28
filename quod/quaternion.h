//
//  quaternion.c
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013
//  http://rosettacode.org/wiki/Simple_Quaternion_type_and_operations#C
//

#ifndef QUOD_QUATERNION_H
#define QUOD_QUATERNION_H

typedef struct quaternion
{
    double q[4];
} quaternion_t;


quaternion_t *quaternion_new(void);
quaternion_t *quaternion_new_set(double q1,
                                 double q2,
                                 double q3,
                                 double q4);

void quaternion_copy(quaternion_t* r, quaternion_t* q);

double quaternion_norm(quaternion_t* q);


void quaternion_neg(quaternion_t* r, quaternion_t* q);

void quaternion_conj(quaternion_t* r, quaternion_t* q);

void quaternion_add_d(quaternion_t* r, quaternion_t* q, double d);

void quaternion_add(quaternion_t* r, quaternion_t* a, quaternion_t* b);

void quaternion_mul_d(quaternion_t* r, quaternion_t* q, double d);
int  quaternion_equal(quaternion_t* a, quaternion_t* b);

void quaternion_mul(quaternion_t* r, quaternion_t* a, quaternion_t* b);

void quaternion_print(quaternion_t* q);

void quaternion_to_rotation_matrix(quaternion_t* q, float* matrix);

#endif // QUOD_QUATERNION_H