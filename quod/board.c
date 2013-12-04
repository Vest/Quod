//
//  board.c
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#include <SDL2/SDL_opengl.h>

#include "board.h"

CellType board[CELL_ROW_MAX * CELL_COL_MAX];

void board_draw_brick(int row, int col);

void board_init() {
    int i = 0;
    for (i = 0; i < CELL_ROW_MAX * CELL_COL_MAX; i++)
        board[i] = EMPTY;
}

void board_render() {
    int row, col;
    glPushMatrix();
    
    glTranslatef(-(CELL_LENGTH + CELL_SPACING_X) * CELL_COL_MAX / 2,
                 -(CELL_WIDTH + CELL_SPACING_Y) * CELL_ROW_MAX / 2,
                 0.0f);
    
    for (row = 0; row < CELL_ROW_MAX; row++)
        for (col = 0; col < CELL_COL_MAX; col++)
            if ((col == 0 && (row == 0 || row == CELL_COL_MAX - 1)) ||
                (col == CELL_ROW_MAX - 1 && (row == 0 || row == CELL_COL_MAX - 1)) ||
                (col == 3 && row == 2))
                continue;
            else
                board_draw_brick(row, col);
    
    // board_draw_brick(0, 0);
    
    glPopMatrix();
}

void board_draw_brick(int row, int col) {
    glPushMatrix();
    
    glTranslatef(col * (CELL_LENGTH + CELL_SPACING_X), row * (CELL_WIDTH + CELL_SPACING_Y), 0.0f);
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, CELL_WIDTH, 0.0f );
    glVertex3f( CELL_LENGTH, 0.0f, 0.0f );
    glVertex3f( CELL_LENGTH, CELL_WIDTH, 0.0f );
    glEnd();
    
    glPopMatrix();
}