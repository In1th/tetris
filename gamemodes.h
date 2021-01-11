/* Gamemodes header file
 * Version: 1.0
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for functions, that runs the scripts for game menu screens, gamemodes and their game over screens
 *
 */

#ifndef GAME_H

#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "block.h"
#include "board.h"
#include "color.h"

/* Initializes all needed allegro addons
 */
void init();

/* That function makes sure that every Allegro component is succesfully initialised
 *
 * param: test - allegro component
 * param: *description - description of that allegro component
 */
void must_init(bool test, const char *description);

/* That funciton operates the tittle screen and switches to different gamemodes
 * [NOTE] NOT CURRENTLY USED
 */
void tittle_screen();

/* That funciton operates the menu screen for gameA
 * [NOTE] NOT CURRENTLY USED
 */
void menuA();

/* That funciton operates the menu screen for gameB
 * [NOTE] NOT CURRENTLY USED
 */
void menuB();

/* That funciton operates the gameA
 * 
 * param *disp - pointer to the ALLEGRO_DISPLAY
 * param: music - music variable of the track that has to be played
 * param: start_level - selected starting level <0,9>
 */
void gameA(ALLEGRO_DISPLAY* disp,char start_level);

/* That funciton operates the gameB
 * 
 * param *disp - pointer to the ALLEGRO_DISPLAY
 * param: start_level - selected starting level <0,9>
 * param: high - number of random blocks at the start of the game <0,5>
 */
void gameB(ALLEGRO_DISPLAY* disp, char start_level, char high);

/* That function operates the Game Over screen for gameA
 *
 * param *disp - pointer to the ALLEGRO_DISPLAY
 * param: *display - pointer to the struct Display containing all required display info
 * [NOTE] NOT CURRENTLY USED
 */
void gameOverA(ALLEGRO_DISPLAY* disp,struct Display *display);

/* That function operates the Game Over screen for gameA
 *
 * param: *display - pointer to the struct Display containing all required display info
 * param: *lines_count - pointer to the start of the array containing how many lines have been cleared, sorted by the number of lines cleared at the same time
 * [NOTE] NOT CURRENTLY USED
 */
void gameOverB(struct Display *display, char *lines_count);

#endif