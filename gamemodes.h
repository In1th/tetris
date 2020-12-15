#ifndef GAME_H

#define GAME_H

void tittle_screen();

void menuA();

void menuB();

void gameA(struct Display *display, char music, char start_level);

void gameB(struct Display *display, char music, char start_level, char high);

void gameOverA(struct DIsplay *display, int score);

void gameOverB(struct Display *display, char *lines_count);

#endif