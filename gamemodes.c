/* Gamemodes file
 * Version: 0.2
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for all the functions in the gamemodes header.
 *
 */

#include "gamemodes.h"

#define min(a,b) (((a)<(b))? (a):(b))
#define max(a,b) (((a)>(b))? (a):(b))

double fallDivident[21] = {53.0,49.0,45.0,41.0,37.0,33.0,28.0,22.0,17.0,11.0,10.0,9.0,8.0,7.0,6.0,6.0,5.0,5.0,4.0,4.0,3.0};

/* TO-DO LIST:
 * 1) gameB():
 *  - make high actually do something
 *  - change statistics
 *  - make an array of lines for the game over screen
 *  - make line counter decrease
 * 2) random block generators
 * 3) game over screens
 * 4) menu for both game types
 * 5) tittle screen
 * 6) music and SFX
 * 7) animations
 * 8) graphics
 * 9) code factorization
 * 10) code optimalization
 *  - global block bitmap, font variables
 *
 */

void must_init(bool test, const char *description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void gameA(char music, char start_level){
	must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 60.0);
    ALLEGRO_TIMER* fallTimer = al_create_timer(fallDivident[min(20,start_level)]/ 60.0);
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0/15.0);
    must_init(drawingTimer, "timer");
    must_init(fallTimer, "timer");
    must_init(moveTimer, "timer");



    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(400, 400);
    must_init(disp, "display");

    /*must_init(al_init_font_addon(), "font addon");
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");*/

    must_init(al_init_image_addon(), "image addon");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fallTimer));
    al_register_event_source(queue, al_get_timer_event_source(drawingTimer));
    al_register_event_source(queue, al_get_timer_event_source(moveTimer));

    bool done = false;
    bool redraw = true;
    bool fall = false;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    //starting timers
    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);
    al_start_timer(moveTimer);

    //seting up display
    struct Display d,*display = &d;

    display -> current_block = generate_block(new_color());
    display -> next_block = generate_block(new_color());
    setup_board(display);
    display -> board_x = 40;
    display -> board_y = 40;

    //seting up the statistics
    char text1[7] = "SCORE:";
    char text2[7] = "LEVEL:";
    char text3[7] = "LINES:";
    char *text_tab[3] = {text1,text2,text3};

    int setup_x = 280, setup_y = 40;

    char i;

    for (i = 0; i< 3; i++){
    	display -> stats[i].x = setup_x;
    	display -> stats[i].y = setup_y + 80*i;
    	if (i == 1)
    		display -> stats[i].value = start_level; 
    	else
    		display -> stats[i].value = 0; 
    	display -> stats[i].label = text_tab[i];
    }

    //things for changing stats
    char lines;
    bool change_score = false;
    int multipliers[4] = {40,100,300,1200};

    //GAME LOOP
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (event.timer.source == fallTimer) fall = true;
                if (event.timer.source == moveTimer){
                    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)) {
                        if (detect_collision(display,-1,0) == 0)
                            (display -> current_block.x)--;
                    }
                    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT)) {
                        if (detect_collision(display,1,0) == 0)
                            (display -> current_block.x)++;
                    }
                }
                if (event.timer.source == drawingTimer) {
                    redraw = true;
                    
                    al_get_keyboard_state(&ks);

                    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)){
                        if (detect_collision(display,0,1) == 0){
                        fall = true;
                        }
                        else {
                            place_block(display);
                            lines = check_for_lines(display);
                            change_score = true;
                            push_next_block(display);
                        }
                    }  
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    reverse_with_collision(display);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_Z){
                    rotate_with_collision(display,0);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_X){
                    rotate_with_collision(display,1);
                    break;
                }
                else break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(fall){
            if (detect_collision(display,0,1) == 0) 
                (display -> current_block.y)++;
            else {
                place_block(display);
                lines = check_for_lines(display);
                change_score = true;
                push_next_block(display);
                if (is_game_over(display) == 1)
                    break;
            }
            fall = false;
        }

        if (change_score){
        	display -> stats[2].value += lines;
        	display -> stats[0].value = min(999999,display -> stats[0].value + multipliers[lines-1] * ((display -> stats[1].value) +1));

        	if (display -> stats[2].value >= 10*(display -> stats[1].value + 1)){
        		display -> stats[1].value++;
        		al_set_timer_speed(fallTimer,fallDivident[min(20,display -> stats[1].value)]/60.0);
        	}

        	change_score = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0,"%s %d",text,d.stats[0].value);

            draw_board(display);
            draw_block(display, 1);

            al_flip_display();

            redraw = false;
        }
    }

    //gameOverA(queue, display);

    al_destroy_display(disp);
    al_destroy_timer(drawingTimer);
    al_destroy_timer(fallTimer);
    al_destroy_timer(moveTimer);
    al_destroy_event_queue(queue);
}

//TODO: THIS!!!!
void gameB(char music, char start_level, char high){
	must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 60.0);
    ALLEGRO_TIMER* fallTimer = al_create_timer(fallDivident[min(20,start_level)]/ 60.0);
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0/15.0);
    must_init(drawingTimer, "timer");
    must_init(fallTimer, "timer");
    must_init(moveTimer, "timer");

	must_init(al_init_image_addon(), "image addon");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(400, 400);
    must_init(disp, "display");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fallTimer));
    al_register_event_source(queue, al_get_timer_event_source(drawingTimer));
    al_register_event_source(queue, al_get_timer_event_source(moveTimer));

    bool done = false;
    bool redraw = true;
    bool fall = false;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);
    al_start_timer(moveTimer);

    struct Display d,*display = &d;

    display -> current_block = generate_block(new_color());
    display -> next_block = generate_block(new_color());
    setup_board(display);
    display -> board_x = 40;
    display -> board_y = 40;

    //seting up the statistics
    char text1[7] = "HIGH:";
    char text2[7] = "LEVEL:";
    char text3[7] = "LINES:";
    char *text_tab[3] = {text1,text2,text3};

    int setup_x = 280, setup_y = 40;

    char i;

    for (i = 0; i< 3; i++){
    	display -> stats[i].x = setup_x;
    	display -> stats[i].y = setup_y + 80*i;
    	if (i == 0)
    		display -> stats[i].value = high; 
    	else if (i == 1)
    		display -> stats[i].value = start_level; 
    	else if (i == 2)
    		display -> stats[i].value = 25; 
    	display -> stats[i].label = text_tab[i];
    }

    char lines;
    bool change_score = false;
    int multipliers[4] = {40,100,300,1200};

    //GAME LOOP
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (event.timer.source == fallTimer) fall = true;
                if (event.timer.source == moveTimer){
                    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)) {
                        if (detect_collision(display,-1,0) == 0)
                            (display -> current_block.x)--;
                    }
                    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT)) {
                        if (detect_collision(display,1,0) == 0)
                            (display -> current_block.x)++;
                    }
                }
                if (event.timer.source == drawingTimer) {
                    redraw = true;
                    
                    al_get_keyboard_state(&ks);

                    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)){
                        if (detect_collision(display,0,1) == 0){
                        fall = true;
                        }
                        else {
                            place_block(display);
                            lines = check_for_lines(display);
                            change_score = true;
                            push_next_block(display);
                        }
                    }  
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    reverse_with_collision(display);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_Z){
                    rotate_with_collision(display,0);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_X){
                    rotate_with_collision(display,1);
                    break;
                }
                else break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done || display -> stats[2].value == 0)
            break;

        if(fall){
            if (detect_collision(display,0,1) == 0) 
                (display -> current_block.y)++;
            else {
                place_block(display);
                lines = check_for_lines(display);
                change_score = true;
                push_next_block(display);
                if (is_game_over(display) == 1)
                    break;
            }
            fall = false;
        }

        if (change_score){
        	display -> stats[2].value = max(0,display -> stats[2].value - lines);
        	
        	change_score = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            draw_board(display);
            draw_block(display, 1);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(drawingTimer);
    al_destroy_timer(fallTimer);
    al_destroy_timer(moveTimer);
    al_destroy_event_queue(queue);

    //gameOverA(display);
}

//MAKE THIS WORK!!!
void gameOverA(ALLEGRO_EVENT_QUEUE* queue, struct Display *display){


	ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    while(1){
		al_wait_for_event(queue, &event);

		switch(event.type){

            case ALLEGRO_EVENT_TIMER:
            	redraw = true;
            	break;

            case ALLEGRO_EVENT_KEY_UP:
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done)
        	break;

        if (redraw){
        	al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "GAME OVER");
        }

	}

	al_destroy_font(font);

}