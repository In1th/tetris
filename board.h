/* Board header file
 * Version: 0.14
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

/* structure containing statistics displayed in-game
 *
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

/* braws the block
 *
 * param: *disp - pointer to a Display struct
 * param: is_on_board - bool value telling the function what block should it draw
 */
//[TODO] MAKE IT DRAW THE NEXT BLOCK
void draw_block(struct Display *disp, char is_on_board);

/* draws entire board
 *
 * param: *disp - pointer to a Display struct
 */
// [TODO] ADD NEXT BLOCK AND STATS TO IT
void draw_board(struct Display *disp);

//[TODO] EVERY FUNCTION BELOW WITH NEEDED STRUCTS AND ARGUMENTS

void draw_statistic(struct Statistics *stat);

void draw_tittle_screen();

void draw_menu_A();

void draw_menu_B();

void draw_game_over_A();

void draw_game_over_B();

#endif