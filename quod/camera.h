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
    point3f pos;        // postion of the camera
    vector3f* dir;  // direction of the sight
    vector3f* up;   // up quaternion
    
    float mSpeed; // movement speed toward the quaternion direction
    float rSpeed; // rotation speed
} camera;

void camera_init();
void camera_render();
void camera_free();

void camera_reset_window(int width, int height);
void camera_accelerate(float step);
void camera_rotate_cw(float step);
void camera_rotate_ccw(float step);

#endif // QUOD_CAMERA_H
