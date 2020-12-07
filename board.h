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
struct BoardBlock{
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
    char x,y;
};

/* structure containing information, that's going to be displayed or to be used in other functions
 *
 * member: board - BOARD_HEIGHT X BOARD_WIDTH array of blocks [not the block that player is controlling]
 * member: board_x, board_y: x,y coordinates of upper-left corner of the board
 * member: stats - array of Statistics structs used in
 *                 a) gameA as:
 *                  a.1) level <1,20>
 *                  a.2) score <0,999999>
 *                  a.3) lines completed <0,+inf]
 *                 b) gameB as:
 *                  b.1) level <1,20>
 *                  b.2) high <0,5>
 *                  b.3) lines left <0,25>
 * member: current_block - block on board that's being controlled by player
 * member: next_block - block that's going to appear after currect_block
 * [NOTE: next_block.x and next_block.y are containing info for the draw function to draw a borded alongside the block]
 */
struct Display{
    struct BoardBlock board[BOARD_HEIGHT][BOARD_WIDTH];
    char board_x, board_y;

    struct Statistics stats[3]; 

    struct Block current_block, next_block;

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

/* detects, if there is a collision with the board blocks, when we move the current_block by dx in x axis and by dy in y axis
 *
 * param: *disp - pointer to a Display struct
 * param: dx, dy: parameters of how we are moving the block {-1,0,1}
 */
char detect_collision(struct Display *disp, char dx,int dy);


#endif