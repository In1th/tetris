/* Gamemodes file
 * Version: 1.0
 * Author: Mateusz Kruk
 * E-mail: krukm634@gmail.com
 *
 * This file contains implementation for all the functions in the gamemodes header.
 *
 */

#include "gamemodes.h"

#define min(a,b) (((a)<(b))? (a):(b))
#define max(a,b) (((a)>(b))? (a):(b))

#define setup_lvl_val(x) x = min(20,x)
#define setup_high_val(x) x = min(5,x)

double fallDivident[21] = {53.0,49.0,45.0,41.0,37.0,33.0,28.0,22.0,17.0,11.0,10.0,9.0,8.0,7.0,6.0,6.0,5.0,5.0,4.0,4.0,3.0};

/* TO-DO LIST:
 * 1) random block generators (sorta fixed)
 * 2) game over screens
 * 3) menu for both game types
 * 4) tittle screen
 * 5) credits
 * 6) music and SFX
 * 7) animations
 * 8) graphics
 * 9) code factorization
 * 10) code optimalization
 *  - global block bitmap, font variables
 *
 */

void init(){
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "font addon");
}

void must_init(bool test, const char *description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void gameA(ALLEGRO_DISPLAY* disp, char start_level){

    //seting up starting values
    setup_lvl_val(start_level);

    //seting up timers
    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 60.0);
    must_init(drawingTimer, "timer");
    ALLEGRO_TIMER* fallTimer = al_create_timer(fallDivident[start_level]/ 60.0);
    must_init(fallTimer, "timer");
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0/15.0);
    must_init(moveTimer, "timer");

    //seting up the queue
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    //adding events to the queue
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fallTimer));
    al_register_event_source(queue, al_get_timer_event_source(drawingTimer));
    al_register_event_source(queue, al_get_timer_event_source(moveTimer));

    //seting up Allegro variables
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    //seting up display
    struct Display d,*display = &d;

    //seting up the game start values
    char text1[7] = "SCORE:";
    char text2[7] = "LEVEL:";
    char text3[7] = "LINES:";
    char *text_tab[3] = {text1,text2,text3};
    int val[3] = {0,start_level,0};

    setup_game(display,"A",text_tab,val);

    //logical variables
    bool done = false;
    bool redraw = true;
    bool over = false;
    char change_score = 0;

    //additional variables
    char lines;
    int multipliers[4] = {40,100,300,1200};

    //starting timers
    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);
    al_start_timer(moveTimer);

    //GAME LOOP
    while(1) {
        al_wait_for_event(queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                    if (event.timer.source == fallTimer && !over) {
                        if (move_down(display) == 0) {
                           lines = check_for_lines(display);
                           change_score = 1;
                        }
                    }
                    if (event.timer.source == moveTimer && !over){
                        if(al_key_down(&ks,ALLEGRO_KEY_LEFT))
                            move_horizontally(display,-1);
                        if(al_key_down(&ks,ALLEGRO_KEY_RIGHT))
                           move_horizontally(display,1);
                    }
                    if (event.timer.source == drawingTimer) {
                        redraw = true;
                    
                        al_get_keyboard_state(&ks);

                        if (al_key_down(&ks, ALLEGRO_KEY_DOWN) && !over){
                            if (move_down(display) == 0){
                                lines = check_for_lines(display);
                                change_score = 2;
                            }
                        }  
                    }  
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (!over)
                    move(display, event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;


        if (change_score && !over){
        	display -> stats[2].value += lines;
            if (lines > 0)
        	   display -> stats[0].value = min(999999,display -> stats[0].value + multipliers[lines-1] * ((display -> stats[1].value) +1));
            else 
                display -> stats[0].value = min(999999,display -> stats[0].value + change_score*4);

        	if (display -> stats[2].value >= 10*(display -> stats[1].value + 1)){
        		display -> stats[1].value = min(20,display -> stats[1].value+1);
        		al_set_timer_speed(fallTimer,fallDivident[display -> stats[1].value]/60.0);
        	}

            if (is_game_over(display) == 1)
                over = true;

        	change_score = false;
        }

        if(redraw && al_is_event_queue_empty(queue)){
            if (over)
                draw_game_over_A(display);
            else
                draw_screen(display);
            redraw = false;
        }

    }    

    al_destroy_timer(drawingTimer);
    al_destroy_timer(fallTimer);
    al_destroy_timer(moveTimer);
    al_destroy_event_queue(queue);
    
    //gameOverA(disp,display);
}


void gameB(ALLEGRO_DISPLAY* disp, char start_level, char high){

    //seting up starting values
    setup_lvl_val(start_level);
    setup_high_val(high);

    //seting up timers
    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 60.0);
    must_init(drawingTimer, "timer");
    ALLEGRO_TIMER* fallTimer = al_create_timer(fallDivident[start_level]/ 60.0);
    must_init(fallTimer, "timer");
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0/15.0);
    must_init(moveTimer, "timer");

    //seting up the queue
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    //adding events to the queue
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fallTimer));
    al_register_event_source(queue, al_get_timer_event_source(drawingTimer));
    al_register_event_source(queue, al_get_timer_event_source(moveTimer));

    //seting up Allegro variables
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    //seting up the game
    struct Display d,*display = &d;

    char text1[7] = "HIGH:";
    char text2[7] = "LEVEL:";
    char text3[7] = "LINES:";
    char *text_tab[3] = {text1,text2,text3};
    int val[3] = {high,start_level,25};

    setup_game(display,"B",text_tab,val);

    //logical values
    bool done = false;
    bool redraw = true;
    char over = 0;
    char change_score = 0;

    //additional variables
    char lines;
    int line_types[5] = {0,0,0,0,0};

    //starting timers
    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);
    al_start_timer(moveTimer);

    //GAME LOOP
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (event.timer.source == fallTimer && over == 0){
                    if (move_down(display) == 0) {
                        lines = check_for_lines(display);
                        change_score = 1;
                    }
                }
                if (event.timer.source == moveTimer && over == 0){
                   if(al_key_down(&ks,ALLEGRO_KEY_LEFT))
                        move_horizontally(display,-1);
                    if(al_key_down(&ks,ALLEGRO_KEY_RIGHT))
                        move_horizontally(display,1);
                }
                if (event.timer.source == drawingTimer) {
                    redraw = true;
                    
                    al_get_keyboard_state(&ks);

                    if (al_key_down(&ks, ALLEGRO_KEY_DOWN) && over == 0){
                        if (move_down(display) == 0) {
                            lines = check_for_lines(display);
                            change_score = 2;
                        }
                    }  
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (over == 0)
                    move(display, event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if (change_score && over == 0){
        	display -> stats[2].value = max(0,display -> stats[2].value - lines);

        	if (lines > 0)
                line_types[lines]++;
        	else 
                line_types[0] += change_score*4;

        	change_score = 0;

            if (is_game_over(display) == 1)
                over = 1;
            if (display -> stats[2].value == 0)
                over = 2;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            if (over == 1)
                draw_game_over_B(display,line_types,0);
            else if (over == 2)
                draw_game_over_B(display,line_types,1);
            else
                draw_screen(display);
            redraw = false;
        }
    }

    al_destroy_timer(drawingTimer);
    al_destroy_timer(fallTimer);
    al_destroy_timer(moveTimer);
    al_destroy_event_queue(queue);
}
