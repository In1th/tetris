#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

#define abs(x) x>0? x: -x

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

/* Structure containing all info about a signle block
 *
 * member: pattern[4][4] - 4x4 array containing location of single block pieces in bits {0, 1}
 * member: r,g,b - contains a value of block's color in RGB
 * member: x,y - contains x and y coodrinates of the upper-left corner of the block
 *
 */

const char oBlock[2][2] = {{1,1},{1,1}};
const char tBlock[3][3] = {{0,0,0},{1,1,1},{0,1,0}};
const char lBlock[3][3] = {{0,1,0},{0,1,0},{0,1,1}};
const char jBlock[3][3] = {{0,1,0},{0,1,0},{1,1,0}};
const char iBlock[4][4] = {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
const char sBlock[4][4] = {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}};
const char zBlock[4][4] = {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}};

struct Block
{
    char pattern[4][4];
    char n;
    ALLEGRO_COLOR color;
    int x,y;
};

//Checks if the block is on the board
//TODO: make it to work with only the block and not array
int is_on_board(int x, int y){
    if ((x > 0) && (BOARD_WIDTH-1 > x) && (y > 0) && (BOARD_HEIGHT-1 > y)) return 1;
    else return 0;
}

//TODO: make this work!
void reverse(struct Block *block){
    char bufor;
    char jump = (block -> n)-1;
    int i,j;

    for(i = 0; i < (block -> n)/2; i++){
        for (j = 0; j < (block -> n); j++){
            bufor = block -> pattern[i+jump][j];
            block -> pattern[i+jump][j] = block -> pattern[i][j];
            block -> pattern[i][j]= bufor;
        }
        jump = jump-2;
    }
}

void rotate(struct Block *block){
    int n = block -> n;

    char bufor[n][n];

    int i,j;

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            bufor[i][j] = block -> pattern[i][j];
        }
    }


    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            block -> pattern[i][j] = bufor[j][n-(i+1)];
        }
    }

}

int randChar(int a,int b){
    int seed;
    time_t tt;
    seed = time(&tt);

    srand(seed);

    int number = rand();

    return (number%b)+a;
}

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
 * [NOTE: has to only work with type 3 and 4 blocks]
 * param: colors[3] - RBG value of the color for the block [default is red]
 *
 * returns: fully initialised BLock structure 
 */
struct Block generate_block(char type, char reversed, unsigned char colors[3]){
    struct Block newBlock;

    int i, j;

    if ( (colors[0] >= 0) && (colors[1] >= 0) && (colors[2] >= 0) ){
        newBlock.color = al_map_rgb(colors[0], colors[1], colors[2]);
    }
    else {
        printf("At least one of the color vaules of the generated block is negative!\n");
        newBlock.color = al_map_rgb(255,0,0);
    }

    newBlock.x = 5;
    newBlock.y = 1;
    

        switch (type){
            case 0: {
                newBlock.n = 2;
                newBlock.x++;
                newBlock.y++;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n) newBlock.pattern[i][j] = oBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }

            } break;
            case 1: {
                newBlock.n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n) newBlock.pattern[i][j] = tBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }
            } break;
            case 2: {
                newBlock.n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n) newBlock.pattern[i][j] = lBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }
            } break;
            case 3: {
                newBlock.n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n)newBlock.pattern[i][j] = jBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }
            } break;
            case 4: {
                newBlock.n = 4;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n)newBlock.pattern[i][j] = sBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }
            } break;
            case 5: {
                newBlock.n = 4;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < newBlock.n && j < newBlock.n) newBlock.pattern[i][j] = zBlock[i][j];
                        else newBlock.pattern[i][j] = 0;
                    }
                }
            } break;
            default: {
                printf("Invalid block type!\n");
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        newBlock.pattern[i][j] = 0;
                    }
                }
            }
        }

        if (reversed == 1){
            reverse(&newBlock);
        }

    return newBlock;
}


void must_init(bool test, const char *description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

//TODO: add the fallen blocks to it
void draw_board(int x, int y, ALLEGRO_BITMAP* bm){

 int i,j;

 for (i = 0; i < BOARD_HEIGHT; i++){
    for (j = 0; j < BOARD_WIDTH; j++){
        if ((BOARD_HEIGHT-1 == i) || (i == 0) || (j == 0) || (BOARD_WIDTH-1 == j) ){
            al_draw_bitmap(bm, (x + 16*j), (y + 16*i), 0);
        }
    }
 }

}

void draw_block(int x, int y,struct Block block, ALLEGRO_BITMAP* bm){
    int i,j;

    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            if (block.pattern[i][j] == 1){
                al_draw_tinted_bitmap(bm, block.color , (x + 16*block.x +16*j), (y + 16*block.y +16*i), 0);
            }
        }
    }
}
