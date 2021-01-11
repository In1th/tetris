/* Color header file
 * Version: 1.0
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This header file contains definitions for functions giving the color values for other modules.
 *
 */

#ifndef COLOR_H

#define COLOR_H

#include <stdio.h>
#include <stdlib.h>

#include "block.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255,255,255)
#define GREY al_map_rgb(211,211,211)
#define RED al_map_rgb(255,0,0)
#define GREEN al_map_rgb(0,255,0)
#define BLUE al_map_rgb(0,0,255)
#define ORANGE al_map_rgb(255,165,0)
#define YELLOW al_map_rgb(255,255,0)
#define PURPLE al_map_rgb(255,0,255)
#define PINK al_map_rgb(255,105,180)

/* Gives a random color from a predifned color palette:
 *					0 - RED
 *					1 - BLUE
 *					2 - GREEN
 *					3 - ORANGE
 *					4 - PINK
 *					5 - YELLOW
 *					6 - PURPLE
 *
 * returns: an ALLEGRO_COLOR struct that cointains the generated color
 */
struct ALLEGRO_COLOR new_color();

#endif