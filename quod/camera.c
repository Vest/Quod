//
//  camera.c
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>

#include "camera.h"
#include "matrix.h"

camera cam;

void camera_init() {
    cam.pos.x = cam.pos.y = 0.0f;
    cam.pos.z = 2.0f;
    
    cam.dir = vector3f_new_set(0.0f, 0.0f, -1.0f);
    cam.up  = vector3f_new_set(0.0f, 1.0f, 0.0);
}

void camera_render() {
    // TO-DO: the camera should generate the matrix only, and only once (until the position is changed).
    // code can be optimized to use one matrices only
    float viewMatrix[16];
    float viewTranslateMatrix[16];
    glLoadIdentity();
    
    vector_to_view_matrix(viewMatrix, cam.dir, cam.up);
    //quaternion_to_rotation_matrix(rotationMatrix, cam.dir);
    //quaternion_to_view_matrix(viewMatrix, cam.dir, cam.up);
    
    matrix_translate_to_position(viewTranslateMatrix, viewMatrix, &cam.pos);
    matrix_transpose_square(viewMatrix, viewTranslateMatrix, 4);
    
    glLoadMatrixf(viewMatrix);
}

// TO-DO: probably create the scene object later and move this code there.
void camera_reset_window(int width, int height) {
    float projectionMatrix[16];
    GLenum error;
    
    if (height <= 0)
		height = 1;
    
	glViewport(0, 0, width, height);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	glSetPerspective(projectionMatrix, 145.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glLoadMatrixf(projectionMatrix);
    error = glGetError();
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void camera_accelerate(float step) {
    cam.pos.x += cam.dir->x * step;
    cam.pos.y += cam.dir->y * step;
    cam.pos.z += cam.dir->z * step;
}

void camera_rotate_cw(float step) {
    quaternion_t* q = quaternion_new_axis_angle(step, cam.dir->x, cam.dir->y, cam.dir->z);
    quaternion_t* p = quaternion_new_set(0.0, cam.up->x, cam.up->y, cam.up->z);
    quaternion_t* q_conj = quaternion_new();
    quaternion_t* tmp = quaternion_new();
    quaternion_t* up_new = quaternion_new();
    quaternion_conj(q_conj, q);
    
    quaternion_mul(tmp, q, p);
    quaternion_mul(up_new, tmp, q_conj);
    
    cam.up->x = up_new->x;
    cam.up->y = up_new->y;
    cam.up->z = up_new->z;
    
    free(up_new);
    free(tmp);
    free(q);
    free(p);
    free(q_conj);
}

void camera_rotate_ccw(float step) {
    camera_rotate_cw(-step);
}

void camera_free() {
    free(cam.dir);
    free(cam.up);
}