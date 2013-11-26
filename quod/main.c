//
//  main.c
//  quod
//
//  Created by Volodin, Vladislav on 25.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <SDL2/SDL.h>

#include "globals.h"
#include "engine.h"

int main(int argc, const char * argv[])
{
#if DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif // DEBUG
    
    if (engine_init())
        return APPLICATION_ERROR;
    
    engine_loop();
    
    engine_stop();
    
    return 0;
}

