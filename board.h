#ifndef UI_H

#define UI_H

#include "block.h"

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

struct BoardBlock{
    char active;
    ALLEGRO_COLOR color;
};

struct Statistics{
    char value;
    char x,y;
};

struct Display{
    struct BoardBlock board[BOARD_HEIGHT][BOARD_WIDTH];
    char board_x, board_y;

    struct Statistics stats[3]; 

    struct Block current_block, next_block;

};

void setup_board(struct Display *disp);
void draw_block(struct Display *disp, char is_on_board);
void draw_board(struct Display *disp);
char detect_collision(struct Display *disp, char dx,int dy);


#endif