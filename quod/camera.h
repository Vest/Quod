//
//  camera.h
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_CAMERA_H
#define QUOD_CAMERA_H

#include "globals.h"
#include "quaternion.h"

typedef struct {
    point3f pos;        // postion of the camera
    quaternion_t* dir;   // direction of the sight
} camera;

void camera_init();
void camera_render();
void camera_free();

void camera_reset_window(int width, int height);

#endif // QUOD_CAMERA_H
