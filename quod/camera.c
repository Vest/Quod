//
//  camera.c
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <SDL2/SDL_opengl.h>
#include <stdlib.h>

#include "camera.h"
#include "matrix.h"

camera cam;

void camera_init() {
    cam.pos.x = cam.pos.y = 0.0f;
    cam.pos.z = 3.0f;
    
    cam.dir = quaternion_new_set(0.0f, 0.0f, -1.0f, 0.0f);
}

void camera_render() {
// TO-DO: the camera should generate the matrix only, and only once (until the position is changed).
    float rotationMatrix[16];
    glLoadIdentity();
    
    quaternion_to_rotation_matrix(cam.dir, rotationMatrix);
    glLoadMatrixf(rotationMatrix);
    glTranslatef(-cam.pos.x, -cam.pos.y, -cam.pos.z);
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

void camera_free() {
    free(cam.dir);
}