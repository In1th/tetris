/* Color file
 * Version: 0.1
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for the functions in the color header.
 *
 */

#include "color.h"

struct ALLEGRO_COLOR new_color(){

	struct ALLEGRO_COLOR color;

	char x = randChar(0,7);

	switch (x){
		case 0: color = RED; break;
		case 1: color = BLUE; break;
		case 2: color = GREEN; break;
		case 3: color = ORANGE; break;
		case 4: color = PINK; break;
		case 5: color = YELLOW; break;
		case 6: color = PURPLE; break;
	}

	return color;
}