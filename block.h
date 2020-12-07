#ifndef BLOCK_H

#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

#define GREY al_map_rgb(211,211,211)
#define RED al_map_rgb(255,0,0)
#define GREEN al_map_rgb(0,255,0)
#define BLUE al_map_rgb(0,0,255)

/* Structure containing all info about a signle block
 *
 * member: pattern[4][4] - 4x4 array containing location of single block pieces in bits {0, 1}
 * member: n - character containing used space of pattern array
 * member: r,g,b - contains a value of block's color in RGB
 * member: x,y - contains x and y coodrinates of the upper-left corner of the block
 *
 */
struct Block
{
    char pattern[4][4];
    char n;
    ALLEGRO_COLOR color;
    int x,y;
};

/* Generates a Block structure from predetermined values
 *
 * param: type - type of the block that has to be generated
 *             { 
 *               0 - O-block,
 *               1 - T-block,
 *               2 - L-block,
 *               3 - J-block,
 *               3 - I-block,
 *               4 - S-block,
 *               5 - Z-block 
 *             }
 * param: inverted - a boolean for triggering the inversion of the block 
 * param: col - RBG value of the color for the block 
 *
 * returns: fully initialised BLock structure 
 */
struct Block generate_block(char type, char reversed, ALLEGRO_COLOR col);

/* Reverses given block
 *
 * param: *block - pointer to the Block structure
 */
void reverse(struct Block *block);

void rotate(struct Block *block);

#endif