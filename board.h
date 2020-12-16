/* Board header file
 * Version: 0.12
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for functions operating on a display.
 *
 */

#ifndef UI_H

#define UI_H

#include "block.h"

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

/* structure containing info about block on the board
 * (not the block that player is controlling)
 *
 * member: active - value telling if draw function has to draw this block {0,1}
 * member: color - RGB value of the block's color
 */
struct Block{
    char active;
    ALLEGRO_COLOR color;
};

/* structure containing statistics displayed in-game
 *
 * member: value - statistic value
 * member: x,y - x,y coordinated of the upper-left corner of the statictic block
 */
struct Statistics{
    char value;
    int x,y;
};

/* structure containing information, that's going to be displayed or to be used in other functions
 *
 * member: board - BOARD_HEIGHT X BOARD_WIDTH array of blocks [not the block that player is controlling]
 * member: board_x, board_y: x,y coordinates of upper-left corner of the board
 * member: game_type - type of the game
 * member: stats - array of Statistics structs used in
 *                 a) gameA as:
 *                  a.1) level <1,20>
 *                  a.2) score <0,999999>
 *                  a.3) lines completed <0,+inf]
 *                 b) gameB as:
 *                  b.1) level <1,20>
 *                  b.2) high <0,5>
 *                  b.3) lines left <0,25>
 * member: current_block - Tetrimino on board that's being controlled by player
 * member: next_block - Tetrimino that's going to appear after currect_block
 * [NOTE: next_block.x and next_block.y are containing info for the draw function to draw a borded alongside the block]
 */
struct Display{
    struct Block board[BOARD_HEIGHT][BOARD_WIDTH];
    int board_x, board_y;

    char game_type;
    struct Statistics stats[3]; 

    struct Tetrimino current_block, next_block;

};

/* generates the border for the board
 *
 * param: *disp - pointer to a Display struct
 */
void setup_board(struct Display *disp);

/* braws the block
 *
 * param: *disp - pointer to a Display struct
 * param: is_on_board - bool value telling the function what block should it draw
 */
void draw_block(struct Display *disp, char is_on_board);

/* draws entire board
 *
 * param: *disp - pointer to a Display struct
 */
void draw_board(struct Display *disp);

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

#endif