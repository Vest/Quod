//
//  camera.c
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

// Use the macro to change the camera position and direction for tests.
// It must be removed later.
// #define QUOD_DEMO

#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>

#include "camera.h"
#include "matrix.h"

camera cam;

void camera_init(void) {
#ifndef QUOD_DEMO
    vector3f dir = { .x = 0.0f, .y = 0.0f, .z = -1.0f };
    vector3f up = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
#else // QUOD_DEMO
    vector3f dir = { .x = 0.4f, .y = 200.0f - 199.1f, .z = -25.0f + 24.6f };
    vector3f up = { .x = 0.0f, .y = 0.0f, .z = 1.0f };
#endif // QUOD_DEMO
    
    float* mRotation = matrix_view_new(&dir, &up);;
    float* mTranslation = NULL;

#ifndef QUOD_DEMO
    cam.pos.x = 0.0f;
    cam.pos.y = 0.0f;
    cam.pos.z = 20.0f;
#else // QUOD_DEMO
    cam.pos.x = 0.0f;
    cam.pos.y = -200.0f;
    cam.pos.z = 25.0f;
#endif // QUOD_DEMO
    
    mTranslation = matrix_translation_new(-cam.pos.x, -cam.pos.y, -cam.pos.z);
    
    cam.mProjection = NULL;
    cam.mWorld = (float*)malloc(sizeof(float) * 16);
    cam.mView = (float*)malloc(sizeof(float) * 16);
    
    matrix_multiplication(cam.mView, mRotation, mTranslation);
    
    cam.q = quaternion_new_matrix(cam.mView);
    
    free(mRotation);
    free(mTranslation);
}

void camera_render(void) {
    float* mTransposedView = (float*)malloc(sizeof(float) * 16);
    
    quaternion_to_rotation_matrix(cam.mView, cam.q);
    matrix_inverse(cam.mWorld, cam.mView);
   
    cam.mWorld[3]  = cam.pos.x;
    cam.mWorld[7]  = cam.pos.y;
    cam.mWorld[11] = cam.pos.z;
    
    matrix_inverse(cam.mView, cam.mWorld);
    
    matrix_transpose_square(mTransposedView, cam.mView, 4);
    
    glLoadMatrixf(mTransposedView);
    free(mTransposedView);
}

// TO-DO: probably create the scene object later and move this code there.
void camera_reset_window(int width, int height) {
    GLenum error;
    
    if (height <= 0)
		height = 1;
    
	glViewport(0, 0, width, height);
    
	glMatrixMode(GL_PROJECTION);
    
	free(cam.mProjection);
    cam.mProjection = matrix_perspective_new(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    
    glLoadMatrixf(cam.mProjection);
    error = glGetError();
    
	glMatrixMode(GL_MODELVIEW);
}

void camera_move_forward(float step) {
    vector3f* forward;
    
    matrix_inverse(cam.mWorld, cam.mView);
    
    forward = vector3f_new_set(-cam.mWorld[2], -cam.mWorld[6], -cam.mWorld[10]);
    
    vector3f_mul_scalar(forward, forward, step);
    vector3f_add(&cam.pos, &cam.pos, forward);
    
    free(forward);
}

void camera_rotate_yaw(float step) {
    quaternion_t* qRotX = quaternion_new_axis_angle(step, 0, 0, -1);
    quaternion_t* qCopy = quaternion_new();
    
    quaternion_mul(qCopy, cam.q, qRotX);
    camera_set_quaternion(qCopy);
    
    free(qCopy);
    free(qRotX);
}

void camera_rotate_pitch(float step) {
    quaternion_t* qRot = quaternion_new_axis_angle(-step, 1, 0, 0);
    quaternion_t* qCopy = quaternion_new();
    
    quaternion_mul(qCopy, qRot, cam.q);
    camera_set_quaternion(qCopy);
    
    free(qCopy);
    free(qRot);
}

void camera_move_right(float step) {
    vector3f* right;
    
    matrix_inverse(cam.mWorld, cam.mView);
    
    right = vector3f_new_set(cam.mWorld[0], cam.mWorld[4], cam.mWorld[8]);
    
    vector3f_mul_scalar(right, right, step);
    vector3f_add(&cam.pos, &cam.pos, right);
    
    free(right);
}

void camera_move_up(float step) {
    vector3f* right;
    
    matrix_inverse(cam.mWorld, cam.mView);
    
    right = vector3f_new_set(cam.mWorld[1], cam.mWorld[5], cam.mWorld[6]);
    
    vector3f_mul_scalar(right, right, step);
    vector3f_add(&cam.pos, &cam.pos, right);
    
    free(right);
}

void camera_set_quaternion(const quaternion_t* q) {
    quaternion_copy(cam.q, q);
    
    quaternion_to_rotation_matrix(cam.mView, cam.q);
    matrix_inverse(cam.mWorld, cam.mView);
    
    cam.mWorld[3] = cam.pos.x;
    cam.mWorld[7] = cam.pos.y;
    cam.mWorld[11] = cam.pos.z;
    
    matrix_inverse(cam.mView, cam.mWorld);
}

void camera_free(void) {
    free(cam.mView);
    free(cam.mWorld);
    free(cam.mProjection);
    free(cam.q);
}