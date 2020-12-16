/* COre file
 * Version: 0.14
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for all the functions in the core header.
 *
 */

#include "core.h"

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

void place_block(struct Display *disp){
    char i,j;

    for (i = 0;i < disp -> current_block.n;i++){
        for (j = 0;j < disp -> current_block.n;j++){
            if (disp -> current_block.pattern[i][j] == 1){
                disp -> board[disp -> current_block.y + i][disp -> current_block.x + j].active = 1;
                disp -> board[disp -> current_block.y + i][disp -> current_block.x + j].color = disp -> current_block.color;
            }
        }
    }
}

//TODO: better random generator that allows only 2 blocks in the row
void push_next_block(struct Display *disp){
    disp -> current_block = disp -> next_block;
    disp -> next_block = generate_block(new_color());
}

//TODO: collision for rotate and reversed blocks
char detect_collision(struct Display *disp, int dx, int dy){
    int i,j;

    int x = disp -> current_block.x;
    int y = disp -> current_block.y;

    for (i = 0; i< (disp -> current_block.n); i++){
        for (j = 0; j< (disp -> current_block.n); j++){
            if (((disp -> board[y+dy+i][x+dx+j].active) == 1)  && ((disp -> current_block.pattern[i][j]) == 1 ))
                return 1;
        }
    }

    return 0;
}

void rotate_with_collision(struct Display *disp, char direction){
    rotate(&(disp -> current_block),direction);

    char is_colliding = detect_collision(disp,0,0);

    if (is_colliding == 1){
        direction = (direction+1)%2;
        rotate(&(disp -> current_block),direction); 
    }
}

void reverse_with_collision(struct Display *disp){

    reverse(&(disp -> current_block));

    char is_colliding = detect_collision(disp,0,0);

    if (is_colliding == 1)
        reverse(&(disp -> current_block)); 

}


void delete_line(struct Display *disp, char line_no){
    char checksum;

    char i,j;

    for (i = line_no; i > 0; i--){
        checksum = 0;
        for (j = 1; j < BOARD_WIDTH-1; j++){
            checksum = checksum + disp -> board[i-1][j].active; 
            disp -> board[i][j].active = disp -> board[i-1][j].active;
            disp -> board[i][j].color = disp -> board[i-1][j].color;
        }
        if (checksum == 0)
            break;
    }
}

//TODO: make an animation
char check_for_lines(struct Display *disp){
    char checksum;
    char max = BOARD_WIDTH-2;

    char i,j;

    char output = 0;

    for (i = BOARD_HEIGHT-2; i > 0; i--){
        checksum = 0;
        for (j = 1; j < BOARD_WIDTH-1; j++){
            checksum = checksum + disp -> board[i][j].active; 
        }
        if (max == checksum){
            output++;
            delete_line(disp,i);
            i++;
        }
    }

    return output;

}

char is_game_over(struct Display *disp){

    char start_collision = detect_collision(disp,0,0);

    return start_collision;
}