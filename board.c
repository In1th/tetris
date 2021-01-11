/* Board file
 * Version: 1.0
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

const char version[4] = "1.0";

void draw_board(struct Display *disp){

 char i,j;

 ALLEGRO_BITMAP* bm = al_load_bitmap(BLOCK_PATH);

 for (i = 0; i < BOARD_HEIGHT; i++){
    for (j = 0; j < BOARD_WIDTH; j++){
        if (disp -> board[i][j].active == 1) 
                al_draw_tinted_bitmap(bm, disp -> board[i][j].color , ((disp -> board_x) + 16*j), ((disp -> board_y) + 16*i), 0);
    }
 }

 for (i = 0; i < 3; i++){
        if (strcmp(disp -> stats[i].label,"SCORE:") == 1)
            draw_statistic(&(disp -> stats[i]),1);
        else
            draw_statistic(&(disp -> stats[i]),0);
}

int x = disp -> stats[2].x;
int y = disp -> stats[2].y + 80;

 for (i = 0; i<6; i++){
        for (j = 0; j<6;j++){
            if (i == 0 || i == 5 || j == 0 || j == 5)
                al_draw_tinted_bitmap(bm, GREY , x + 16*j, y + 16*i, 0);
            else
                if (disp -> next_block.pattern[i-1][j-1] == 1){
                    if (disp -> next_block.n == 2)
                        al_draw_tinted_bitmap(bm, disp -> next_block.color , x + 16 + 16*j, y + 16 + 16*i, 0);
                    else
                        al_draw_tinted_bitmap(bm, disp -> next_block.color , x + 16*j, y + 16*i, 0);

                }
        }
    }

 al_destroy_bitmap(bm);

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

    al_destroy_bitmap(bm);
}

void draw_statistic(struct Statistics *stat, char is_score){

    char i,j;

    ALLEGRO_FONT *font = al_create_builtin_font(); 

    ALLEGRO_BITMAP* bm = al_load_bitmap(BLOCK_PATH);

    for (i = 0; i<4; i++){
        for (j = 0; j<6;j++){
            if (i == 0 || i == 3 || j == 0 || j == 5)
                al_draw_tinted_bitmap(bm, GREY , (stat -> x) + 16*j, (stat -> y) + 16*i, 0);
        }
    }

    if (is_score)
        al_draw_multiline_textf(font,WHITE,(stat -> x) + 16, (stat -> y) + 16,64,16,0,"%s\n%06d",stat -> label,stat -> value);
    else
        al_draw_multiline_textf(font,WHITE,(stat -> x) + 16, (stat -> y) + 16,64,16,0,"%s\n%d",stat -> label,stat -> value);

    al_destroy_bitmap(bm);
    al_destroy_font(font);

}

void draw_screen(struct Display *disp){

    ALLEGRO_FONT *font = al_create_builtin_font();

    al_clear_to_color(BLACK);
    al_draw_textf(font, WHITE, 0, 380, 0," Tetris version: %s 2021 by Mateusz Kruk",version);

    draw_board(disp);
    draw_block(disp, 1);

    al_flip_display();
    al_destroy_font(font);
}

void draw_border(struct Display *disp){
    char i,j;

    ALLEGRO_BITMAP* bm = al_load_bitmap(BLOCK_PATH);

    for (i = 0; i < BOARD_HEIGHT; i++){
        for (j = 0; j < BOARD_WIDTH; j++){
            if ((BOARD_HEIGHT-1 == i) || (i == 0) || (j == 0) || (BOARD_WIDTH-1 == j) )
                al_draw_tinted_bitmap(bm, disp -> board[i][j].color , ((disp -> board_x) + 16*j), ((disp -> board_y) + 16*i), 0);
    }
 }

    for (i = 0; i < 3; i++){
        if (strcmp(disp -> stats[i].label,"SCORE:") == 1)
            draw_statistic(&(disp -> stats[i]),1);
        else
            draw_statistic(&(disp -> stats[i]),0);
    }

    int x = disp -> stats[2].x;
    int y = disp -> stats[2].y + 80;

    for (i = 0; i<6; i++){
        for (j = 0; j<6;j++){
            if (i == 0 || i == 5 || j == 0 || j == 5)
                al_draw_tinted_bitmap(bm, GREY , x + 16*j, y + 16*i, 0);
            else
                if (disp -> next_block.pattern[i-1][j-1] == 1){
                    if (disp -> next_block.n == 2)
                        al_draw_tinted_bitmap(bm, disp -> next_block.color , x + 16 + 16*j, y + 16 + 16*i, 0);
                    else
                        al_draw_tinted_bitmap(bm, disp -> next_block.color , x + 16*j, y + 16*i, 0);

                }
        }
    }

    al_destroy_bitmap(bm);
}

void draw_game_over_A(struct Display *disp){
    ALLEGRO_FONT *font1 = al_create_builtin_font();
    ALLEGRO_FONT *font2 = al_load_font("font.otf",32,0);
    ALLEGRO_FONT *font3 = al_load_font("font.otf",20,0);

    al_clear_to_color(BLACK);
    al_draw_textf(font1, WHITE, 0, 380, 0," Tetris version: %s 2021 by Mateusz Kruk",version);

    al_draw_text(font2, WHITE,38,84,0,"GAME OVER!");

    if (disp ->stats[0].value == 999999)
        al_draw_textf(font3, WHITE,131,200,ALLEGRO_ALIGN_CENTER,"GOOD JOB!");
    else
        al_draw_textf(font3, WHITE,131,200,ALLEGRO_ALIGN_CENTER,"TRY AGAIN!");

    draw_border(disp);

    al_flip_display();
    al_destroy_font(font1);
    al_destroy_font(font2);
    al_destroy_font(font3);
}

void draw_game_over_B(struct Display *disp,int *lines, char success){
    ALLEGRO_FONT *font1 = al_create_builtin_font();
    ALLEGRO_FONT *font2 = al_load_font("font.otf",32,0);

    const float font_size = 18;

    ALLEGRO_FONT *font3 = al_load_font("font.otf",font_size,0);

    al_clear_to_color(BLACK);
    al_draw_textf(font1, WHITE, 0, 380, 0," Tetris version: %s 2021 by Mateusz Kruk",version);

    if (success){
        int multipliers[4] = {400,1000,3000,12000};
        int x = 20 + font_size + 2;

        char single[7] = "SINGLE";
        char doub[7] = "DOUBLE";
        char triple[7] = "TRIPLE";
        char tetris[7] = "TETRIS";
        char stage[11] = "THIS STAGE";

        char *l[4] = {single,doub,triple,tetris};

        char i; 
        int *bufor = lines, sum = *lines;
        int score[4];

        for (i = 0; i < 4; i++){
            bufor++;
            al_draw_text(font3,WHITE,x,20+font_size + 3*font_size*i,0,l[i]);
            al_draw_textf(font3,WHITE,x,20+font_size + 3*font_size*i+font_size,0,"%2d  X  %d",*bufor,multipliers[i]);
            score[i] = (*bufor)*(multipliers[i]);
            sum += score[i];
            al_draw_textf(font3,WHITE,x,20+font_size + 3*font_size*i+2*font_size,0,"       %d",score[i]);
        }

        al_draw_text(font3,WHITE,x,20+13*font_size,0,"DROPS");
        al_draw_textf(font3,WHITE,x,20+14*font_size,0,"     %4d",*lines);

        al_draw_text(font3,WHITE,x,20+15*font_size,0,"-----------------");
        al_draw_text(font3,WHITE,x,20+16*font_size,0,"THIS STAGE");
        al_draw_textf(font3,WHITE,x,20+17*font_size,0,"    %6d",sum);

    }
    else {
        al_draw_text(font2, WHITE,38,84,0,"GAME OVER!");
        al_draw_textf(font3, WHITE,131,200,ALLEGRO_ALIGN_CENTER,"TRY AGAIN!");
    }

    draw_border(disp);

    al_flip_display();
    al_destroy_font(font1);
    al_destroy_font(font2);
    al_destroy_font(font3);
}