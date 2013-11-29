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

typedef union quaternion
{
    double q[4];
    struct {
        double w, x, y, z;
    };
} quaternion_t;


quaternion_t* quaternion_new(void);
quaternion_t* quaternion_new_set(double w,
                                 double x,
                                 double y,
                                 double z);
quaternion_t* quaternion_new_axis_angle(double degrees,
                                        double x,
                                        double y,
                                        double z);

void quaternion_copy(quaternion_t* r, const quaternion_t* q);

double quaternion_norm(quaternion_t* q);
void quaternion_normalize(quaternion_t* q);

void quaternion_neg(quaternion_t* r, quaternion_t* q);

void quaternion_conj(quaternion_t* r, quaternion_t* q);

void quaternion_add_d(quaternion_t* r, const quaternion_t* q, double d);

void quaternion_add(quaternion_t* r, quaternion_t* a, quaternion_t* b);

void quaternion_mul_d(quaternion_t* r, quaternion_t* q, double d);
int  quaternion_equal(quaternion_t* a, quaternion_t* b);

void quaternion_mul(quaternion_t* r, quaternion_t* a, quaternion_t* b);

void quaternion_print(quaternion_t* q);

void quaternion_to_rotation_matrix(float* matrix, quaternion_t* q);
void quaternion_to_view_matrix(float* matrix, quaternion_t* q, quaternion_t* up);

double quaternion_get_deg_angle(const quaternion_t* q);
double quaternion_get_rad_angle(const quaternion_t* q);

void quaternion_set_deg_angle(quaternion_t* q, double a);
void quaternion_set_rad_angle(quaternion_t* q, double a);

#endif // QUOD_QUATERNION_H