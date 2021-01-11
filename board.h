/* Board header file
 * Version: 1.0
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for functions operating on a display.
 *
 */

#ifndef UI_H

#define UI_H

#include "block.h"
#include <string.h>

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

/* structure containing statistics displayed in-game
 *
 * member: *label - label of the statistic box
 * member: value - statistic value
 * member: x,y - x,y coordinated of the upper-left corner of the statictic block
 */
struct Statistics{
	char *label;
    int value;
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
 *					b.1) high <0,5>
 *                  b.2) level <1,20>
 *                  b.3) lines left <0,25>
 * member: current_block - Tetrimino on board that's being controlled by player
 * member: next_block - Tetrimino that's going to appear after currect_block
 */
struct Display{
    struct Block board[BOARD_HEIGHT][BOARD_WIDTH];
    int board_x, board_y;

    char game_type;
    struct Statistics stats[3]; 

    struct Tetrimino current_block, next_block;

};

/* draws the block
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

/* Draws the statistic box
 *
 * param: *stat - pointer to a Statistics struct
 * param: is_score - a bool value if stats[0] holds a value for score
 */
void draw_statistic(struct Statistics *stat,char is_score);

/* draws game screen
 *
 * param: *disp - pointer to a Display struct
 */
void draw_screen(struct Display *disp);

/* draws game screen but without the placed blocks
 *
 * param: *disp - pointer to a Display struct
 */
void draw_border(struct Display *disp);

/* draws game over screen for gameA
 *
 * param: *disp - pointer to a Display struct
 */
void draw_game_over_A(struct Display *disp);

/* draws game over screen for gameB
 *
 * param: *disp - pointer to a Display struct
 * param: *lines - pointer to an array contaiting line types values
 * param: success - bool value if the player cleared 25 lines
 */
void draw_game_over_B(struct Display *disp,int *lines, char success);

#endif