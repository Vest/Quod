//
//  matrix.h
//  quod
//
//  Created by Volodin, Vladislav on 27.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_MATRIX_H
#define QUOD_MATRIX_H

void glSetPerspective(float* matrix,
                      float fovyInDegrees, float aspectRatio,
                      float znear, float zfar);
void glSetFrustum(float* matrix,
                  float left, float right, float bottom, float top,
                  float znear, float zfar);
#endif
