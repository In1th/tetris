/* Block file
 * Version: 0.12
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for all the functions in the block header.
 *
 */

#include "block.h"

//constant block patterns
static const char oBlock[2][2] = {{1,1},{1,1}};
static const char tBlock[3][3] = {{0,0,0},{1,1,1},{0,1,0}};
static const char lBlock[3][3] = {{0,1,0},{0,1,0},{0,1,1}};
static const char jBlock[3][3] = {{0,1,0},{0,1,0},{1,1,0}};
static const char iBlock[4][4] = {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
static const char sBlock[4][4] = {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}};
static const char zBlock[4][4] = {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}};

char randChar(char a,char b){

    char number = (rand()%b)+a;

    return number;
}

void generate_block(struct Tetrimino *t, ALLEGRO_COLOR col){

    char type = randChar(0,7);

    int i, j;

    t -> color = col;

    t -> x = 5;
    t -> y = 1;
    

        switch (type){
            case 0: {
                t -> n = 2;
                t -> x++;
                t -> y++;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n) t -> pattern[i][j] = oBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }

            } break;
            case 1: {
                t -> n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n) t -> pattern[i][j] = tBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            case 2: {
                t -> n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n) t -> pattern[i][j] = lBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            case 3: {
                t -> n = 3;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n)t -> pattern[i][j] = jBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            case 4: {
                t -> n = 4;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n)t -> pattern[i][j] = iBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            case 5: {
                t -> n = 4;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n)t -> pattern[i][j] = sBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            case 6: {
                t -> n = 4;
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        if (i < t -> n && j < t -> n) t -> pattern[i][j] = zBlock[i][j];
                        else t -> pattern[i][j] = 0;
                    }
                }
            } break;
            default: {
                printf("Invalid block type!\n");
                for (i = 0; i< 4; i++){
                    for (j = 0;j<4;j++){
                        t -> pattern[i][j] = 0;
                    }
                }
            }
        }
}

void reverse(struct Tetrimino *block){
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

void rotate(struct Tetrimino *block, char direction){
    int n = block -> n;

    char bufor[n][n];

    int i,j;

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            bufor[i][j] = block -> pattern[i][j];
        }
    }

    if (direction == 0){
    	for (i = 0; i < n; i++){
        	for (j = 0; j < n; j++){
            	block -> pattern[i][j] = bufor[j][n-(i+1)];
        	}
    	}
    }

    else if (direction == 1){ 
    	for (i = 0; i < n; i++){
        	for (j = 0; j < n; j++){
            	block -> pattern[i][j] = bufor[n-(j+1)][i];
        	}
    	}
	}

}
