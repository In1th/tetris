#ifndef COLOR_H

#define COLOR_H

#include <stdio.h>
#include <stdlib.h>

#include "block.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define GREY al_map_rgb(211,211,211)
#define RED al_map_rgb(255,0,0)
#define GREEN al_map_rgb(0,255,0)
#define BLUE al_map_rgb(0,0,255)
#define ORANGE al_map_rgb(255,165,0)
#define YELLOW al_map_rgb(255,255,0)
#define PURPLE al_map_rgb(255,0,255)
#define PINK al_map_rgb(255,105,180)

struct ALLEGRO_COLOR new_color();

#endif