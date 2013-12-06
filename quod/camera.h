//
//  camera.h
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_CAMERA_H
#define QUOD_CAMERA_H

#include "vector.h"
#include "globals.h"
#include "quaternion.h"

typedef struct {
    vector3f pos;    // camera position
    quaternion_t* q; // camera quaternion
    
    // World x View x Projection
    float* mWorld;
    float* mView;
    float* mProjection;
} camera;

void camera_init(void);
void camera_render(void);
void camera_free(void);

void camera_reset_window(int width, int height);
void camera_move_forward(float step);
void camera_rotate_yaw(float step);
void camera_rotate_pitch(float step);
void camera_rotate_roll(float step);
void camera_move_right(float step);
void camera_move_up(float step);

void camera_set_quaternion(const quaternion_t* q);
#endif // QUOD_CAMERA_H
