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

/* private variables */
SDL_Window* mainWindow  = NULL;
SDL_GLContext glContext = NULL;
SDL_bool bRunning = SDL_TRUE;

/* private functions */
int engine_opengl_init();

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
    
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Initialization - finished\n");
    
    return 0;
}

void engine_stop() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye-bye!\n");
}

void engine_loop() {
    SDL_Event event;
    SDL_Event evCustom; // custom events used for communication
    
    /* time measure */
    Uint32 tCurrent = 0,
    tDelta = 0,
    tLast = 0,
    tPassed = 0; // passed time
    
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
            }
        }
        
        if (tPassed >= TIME_STEP) {
            tPassed -= TIME_STEP;
        }
    }
}