#include "block.h"
#include "board.h"

#define BLOCK_PATH "block.png"

//currently not used
#define abs(x) x>0? x: -x

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

void setup_board(struct Display *disp){
    char i,j;

    for (i = 0; i < BOARD_HEIGHT; i++){
        for (j = 0; j < BOARD_WIDTH; j++){
            if ((BOARD_HEIGHT-1 == i) || (i == 0) || (j == 0) || (BOARD_WIDTH-1 == j) ){
                disp -> board[i][j].active = 1;
                disp -> board[i][j].color = GREY;
        }
            else {
                disp -> board[i][j].active = 0;
            }
    }
 }
}

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
    int i,j;

    struct Block block;

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

char detect_collision(struct Display *disp, char dx, int dy){
    int i,j;

    int x = disp -> current_block.x;
    int y = disp -> current_block.y;

    for (i = 0; i< (disp -> current_block.n); i++){
        for (j = 0; j< (disp -> current_block.n); j++){
            if (((disp -> board[y+dy+i][x+dx+j].active) == 1)  && ((disp -> current_block.pattern[y+i][x+j]) == 1 ))
                return 1;
        }
    }

    return 0;
}