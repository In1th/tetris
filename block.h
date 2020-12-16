/* Block header file
 * Version: 0.11
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for functions operating on a single tetrimino.
 *
 */

#ifndef BLOCK_H

#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

/* Structure containing all info about a signle block
 *
 * member: pattern[4][4] - 4x4 array containing location of single block pieces in bits {0, 1}
 * member: n - character containing used space of pattern array
 * member: r,g,b - contains a value of block's color in RGB
 * member: x,y - contains x and y coodrinates of the upper-left corner of the block
 *
 */
struct Tetrimino
{
    char pattern[4][4];
    char n;
    ALLEGRO_COLOR color;
    int x,y;
};

int randChar(int a,int b);

/* Generates a Tetrimino structure from predetermined values and one of those types:
 *               0 - O-block,
 *               1 - T-block,
 *               2 - L-block,
 *               3 - J-block,
 *               4 - I-block,
 *               5 - S-block,
 *               6 - Z-block 
 *
 * param: col - RBG value of the color for the block 
 *
 * returns: fully initialised Tetrimino structure 
 */
struct Tetrimino generate_block(ALLEGRO_COLOR col);

/* Reverses given Tetrimino
 *
 * param: *block - pointer to the Block structure
 * param: direction - what direction the block has to rotate (0 - left, 1 - right)
 */
void reverse(struct Tetrimino *block, char direction);

/* ROtates given Tetrimino
 *
 * param: *block - pointer to the Block structure
 */
void rotate(struct Tetrimino *block);

#endif