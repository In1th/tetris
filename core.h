/* Board header file
 * Version: 0.14
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for all base mechanics for the game.
 *
 */

#ifndef CORE_H

#define CORE_H

#include "block.h"
#include "board.h"

/* generates the border for the board
 *
 * param: *disp - pointer to a Display struct
 */
void setup_board(struct Display *disp);

void setup_high(struct Display *disp, char high);

void setup_game(struct Display *disp,char *mode, char **labels, int values[3]);

/* places fallen block on board
 *
 * param: *disp - pointer to a Display struct
 */
void place_block(struct Display *disp);

/* puts next block on the line
 *
 * param: *disp - pointer to a Display struct
 */
void push_next_block(struct Display *disp);

/* detects, if there is a collision with the board blocks, when we move the current_block by dx in x axis and by dy in y axis
 *
 * param: *disp - pointer to a Display struct
 * param: dx, dy: parameters of how we are moving the block {-1,0,1}
 */
char detect_collision(struct Display *disp, int dx,int dy);

/* detects, if there is a collision with the board blocks, when we rotate the current_block in given direction
 *
 * param: *disp - pointer to a Display struct
 * param: dicrection: what direction the block has to rotate (0 - left, 1 - right)
 */
void rotate_with_collision(struct Display *disp, char direction);

/* detects, if there is a collision with the board blocks, when we reverse the current_block 
 *
 * param: *disp - pointer to a Display struct
 */
void reverse_with_collision(struct Display *disp);

/* delets given line from the board and decrements all the lines y-axis above it
 *
 * param: *disp - pointer to a Display struct
 * param: line_no - line index to delete
 *
 * returns: true (1) or false (0) value for collision
 */
void delete_line(struct Display *disp, char line_no);

/* checks how many lines were filled
 *
 * param: *disp - pointer to a Display struct
 *
 * returns: a number of filled lines <0,4>
 */
char check_for_lines(struct Display *disp);

/* Checks if the current_block at the start collides with the board, hence the if the game is over
 *
 * param: *disp - pointer to a Display struct
 *
 * returns: true (1) or false (0) value for game over condition
 */
char is_game_over(struct Display *disp);

void move(struct Display *disp, int keycode);
void move_horizontally(struct Display *disp, char direction);
char move_down(struct Display *disp);

#endif