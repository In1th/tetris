/* Tetris
 * Version: 0.1
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

int main(){

    gameA(1,1);

    return 0;
}


