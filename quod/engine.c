//
//  engine.c
//  quod
//
//  Created by Volodin, Vladislav on 25.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "globals.h"
#include "engine.h"
#include "board.h"
#include "camera.h"

/* private variables */
SDL_Window* mainWindow  = NULL;
SDL_GLContext glContext = NULL;
SDL_bool bRunning = SDL_TRUE;

/* private functions */
int engine_opengl_init();
void engine_render_frame();

int engine_init() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Engine Initialization - started\n");
    
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize engine\n"
                     "Error: %s\n", SDL_GetError());
        
        return ENGINE_ERROR;
    }
    
    mainWindow = SDL_CreateWindow("Quod",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  640, 480,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (mainWindow == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window\n"
                     "Error: %s\n", SDL_GetError());
        
        return ENGINE_ERROR;
    }
    
    if (engine_opengl_init())
        return ENGINE_ERROR;
    
    board_init();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Engine Initialization - finished\n");
    return 0;
}

int engine_opengl_init() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Initialization - started\n");
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    glContext = SDL_GL_CreateContext(mainWindow);
    if (glContext == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create OpenGL context\n"
                     "Error: %s\n", SDL_GetError());
        
        return ENGINE_ERROR;
    }
    
    camera_init();
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Initialization - finished\n");
    
    return 0;
}

void engine_stop() {
    camera_free();
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye-bye!\n");
}

void engine_loop() {
    SDL_Event event;
    SDL_Event evCustom; // custom events used for communication
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    /* time measure */
    Uint32 tCurrent = 0,
    tDelta = 0,
    tLast = 0,
    tPassed = 0; // passed time
    
    camera_reset_window(640, 480);
    
    while (bRunning == SDL_TRUE) {
        tCurrent = SDL_GetTicks();
        tDelta = tCurrent - tLast;
        tLast = tCurrent;
        tPassed += tDelta;
        
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Quit timestamp: %dms\n", event.quit.timestamp);
                    
                    bRunning = SDL_FALSE;
                    break;
                    
                    /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            evCustom.type = SDL_QUIT;
                            evCustom.quit.timestamp = 0;
                            
                            SDL_PushEvent(&evCustom);
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Window %d resized to %dx%d",
                                         event.window.windowID,
                                         event.window.data1, event.window.data2);
                            camera_reset_window(event.window.data1, event.window.data2);
                            break;
                    }
                    break;
            }
        }
        
        if (tPassed >= TIME_STEP) {
            tPassed -= TIME_STEP;
            
            float step = 0.5f;
            
            if (keys[SDL_SCANCODE_UP])
                camera_move_forward(step);
            else if (keys[SDL_SCANCODE_DOWN])
                camera_move_forward(-step);
            
            if (keys[SDL_SCANCODE_RIGHT])
                camera_rotate_yaw(step * 2);
            else if (keys[SDL_SCANCODE_LEFT])
                camera_rotate_yaw(-step * 2);
            
            if (keys[SDL_SCANCODE_E])
                camera_rotate_pitch(step);
            else if (keys[SDL_SCANCODE_Q])
                camera_rotate_pitch(-step);
            
            if (keys[SDL_SCANCODE_D])
                camera_move_right(step);
            else if (keys[SDL_SCANCODE_A])
                camera_move_right(-step);
            
            if (keys[SDL_SCANCODE_W])
                camera_move_up(step);
            else if (keys[SDL_SCANCODE_S])
                camera_move_up(-step);
        }
        
        engine_render_frame();
        
        SDL_GL_SwapWindow(mainWindow);
    }
}

void engine_render_frame() {
    glClear( GL_COLOR_BUFFER_BIT );
    camera_render();
    board_render();
}