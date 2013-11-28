//
//  board.h
//  quod
//
//  Created by Volodin, Vladislav on 26.11.13.
//  Copyright (c) 2013 Volodin, Vladislav. All rights reserved.
//

#ifndef QUOD_BOARD_H
#define QUOD_BOARD_H

/* logical state */
#define CELL_ROW_MAX  11
#define CELL_COL_MAX  11
#define EXCLUDE_CORNERS 1

typedef enum {
    EMPTY = 0,
    BLUE,
    RED,
    BLOCK
} CellType;

/* update state */
#define CELL_LENGTH  1.0f
#define CELL_WIDTH   1.0f
#define CELL_HEIGHT  0.01f

#define CELL_SPACING_X 0.01f
#define CELL_SPACING_Y 0.01f

void board_init();
void board_render();

#endif // QUOD_BOARD_H
