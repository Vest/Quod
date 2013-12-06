//
//  engine.h
//  quod
//
//  Created by Volodin, Vladislav on 25.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_ENGINE_H
#define QUOD_ENGINE_H

int  engine_init(void);
void engine_stop(void);
void engine_loop(void);

void engine_handle_mouse(SDL_MouseMotionEvent* mouseEvent);

#endif // QUOD_ENGINE_H
