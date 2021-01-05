/* Tetris
 * Version: 0.2
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file is the main file for the tetris game.
 *
 * [NOTE] in order to compile it using unix commands, you have to use a flag:
 * $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
 */

#include "board.c"
#include "block.c"
#include "color.c"
#include "core.c"
#include "gamemodes.c"
#include <string.h>

int main(int argc, char *argv[]){

    srand(time(NULL));

    //TODO: IMPLEMENT DIFFERENT GENERATOR ALGORITHMS
    switch (argc){
        /* no arguments 
         * [PLAYS THE TITTLE SCREEN]
         */
        case 1:
            //tittle_screen();
            gameA(1,0); //placeholrder
            break;
        /* 1 argument 
         * [PLAYS THE CHOSEN GAMEMODE MENU OR CREDITS]
         */
        case 2: 
            if (strcmp(argv[1],"A") == 0)
                gameA(1,0);
            else if (strcmp(argv[1],"B") == 0)
                gameB(1,0,0);
            //else play the credits
            break;
        /* 3 arguments 
         *[PLAYS GAME A WITH GIVEN ARGUMENTS AND WITHOUT CHOOSING THE GENERATOR ALGORITHM] 
         */
        case 4:
            if (strcmp(argv[1],"A") == 0){
                char song = atoi(argv[2]), level = atoi(argv[3]);
                gameA(song,level);
            }
            break;
        /* 4 arguments 
         *[PLAYS GAME B WITH GIVEN ARGUMENTS AND WITHOUT CHOOSING THE GENERATOR ALGORITHM] 
         * or
         *[PLAYS GAME A WITH GIVEN ARGUMENTS AND WITH CHOOSING THE GENERATOR ALGORITHM] 
         */
        case 5:
            if (strcmp(argv[1],"B") == 0){
                char song = atoi(argv[2]), level = atoi(argv[3]), high = atoi(argv[4]);
                gameB(song,level,high);
            }
            break;
        /* 5 arguments
         *[PLAYS GAME B WITH GIVEN ARGUMENTS AND WITH CHOOSING THE GENERATOR ALGORITHM] 
         */
        case 6:
            break;
        default:
            printf("ERROR! INCORRECT NUMBER OF ARGUMENTS!\n");
            return 2;
        }

    return 0;
}


