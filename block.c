#include "block.h"

//constant block patterns
static const char oBlock[2][2] = {{1,1},{1,1}};
static const char tBlock[3][3] = {{0,0,0},{1,1,1},{0,1,0}};
static const char lBlock[3][3] = {{0,1,0},{0,1,0},{0,1,1}};
static const char jBlock[3][3] = {{0,1,0},{0,1,0},{1,1,0}};
static const char iBlock[4][4] = {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
static const char sBlock[4][4] = {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}};
static const char zBlock[4][4] = {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}};

struct Block generate_block(char type, char reversed, ALLEGRO_COLOR col){
    struct Block newBlock;

    int i, j;

    newBlock.color = col;

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
