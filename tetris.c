/* Tetris
 * Version: 1.0
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file is the main file for the tetris game.
 *
 * [NOTE] in order to compile it using unix commands, you have to use a flag:
 * $(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
 */

#include "board.c"
#include "block.c"
#include "color.c"
#include "core.c"
#include "gamemodes.c"

int main(int argc, char *argv[]){

    init();

    ALLEGRO_DISPLAY* disp = al_create_display(400, 400);
    must_init(disp, "display");

    srand(time(NULL));

    //TODO: IMPLEMENT DIFFERENT GENERATOR ALGORITHMS
    switch (argc){
        /* no arguments 
         * [PLAYS GAME A]
         */
        case 1:
            gameA(disp,0);
            break;
        /* 1 argument 
         * [PLAYS THE CHOSEN GAMEMODE WITH DEFAULT ARGUMENTS]
         */
        case 2: 
            if (strcmp(argv[1],"A") == 0)
                gameA(disp,0);
            else if (strcmp(argv[1],"B") == 0)
                gameB(disp,0,0);
            break;
        /* 3 arguments 
         *[PLAYS GAME A WITH GIVEN ARGUMENTS] 
         */
        case 3:
            if (strcmp(argv[1],"A") == 0){
                char level = atoi(argv[2]);
                gameA(disp,level);
            }
            break;
        /* 4 arguments 
         *[PLAYS GAME B WITH GIVEN ARGUMENTS] 
         */
        case 4:
            if (strcmp(argv[1],"B") == 0){
                char level = atoi(argv[2]), high = atoi(argv[3]);
                gameB(disp,high,level);
            }
            break;
        default:
            printf("ERROR! INCORRECT NUMBER OF ARGUMENTS!\n");
            return 2;
        }

    al_destroy_display(disp);

    return 0;
}


