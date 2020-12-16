/* Board file
 * Version: 0.14
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for all the functions in the board header.
 *
 */

#include "block.h"
#include "board.h"
#include "color.h"

#define BLOCK_PATH "block.png"

void draw_board(struct Display *disp){

 char i,j;

 ALLEGRO_BITMAP* bm = al_load_bitmap(BLOCK_PATH);

 for (i = 0; i < BOARD_HEIGHT; i++){
    for (j = 0; j < BOARD_WIDTH; j++){
        if (disp -> board[i][j].active == 1) 
                al_draw_tinted_bitmap(bm, disp -> board[i][j].color , ((disp -> board_x) + 16*j), ((disp -> board_y) + 16*i), 0);
    }
 }

}

void draw_block(struct Display *disp, char is_on_board){
    char i,j;

    struct Tetrimino block;

     ALLEGRO_BITMAP* bm = al_load_bitmap(BLOCK_PATH);

    if (is_on_board == 1){
        block = disp -> current_block;
    }
    else {
        block = disp -> next_block;
    }
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            if (block.pattern[i][j] == 1){
                al_draw_tinted_bitmap(bm, block.color , ((disp -> board_x) + 16*block.x +16*j), ((disp -> board_y) + 16*block.y +16*i), 0);
            }
        }
    }
}

