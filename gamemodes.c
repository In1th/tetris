
#include "gamemodes.h"

void must_init(bool test, const char *description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void gameA(char music, char start_level){
	must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 30.0);
    ALLEGRO_TIMER* fallTimer = al_create_timer(1.0 / 0.8);
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0/15.0);
    must_init(drawingTimer, "timer");
    must_init(fallTimer, "timer");
    must_init(moveTimer, "timer");



    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(400, 400);
    must_init(disp, "display");

    must_init(al_init_font_addon(), "font addon");
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* block = al_load_bitmap("block.png");
    must_init(block, "block");

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

    char text[6] = "SCORE:";

    display -> stats[0].x = 280;
    display -> stats[0].y = 40;
    display -> stats[0].value = 0;
    display -> stats[0].label = text;

    display -> stats[1].x = 280;
    display -> stats[1].y = 120;
    display -> stats[0].label = text;

    display -> stats[2].x = 280;
    display -> stats[2].y = 200;
    display -> stats[0].label = text;

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
                        fall = false;
                        (display -> current_block.y)++;
                        }
                        else {
                            place_block(display);
                            display -> stats[0].value += check_for_lines(display);
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
                display -> stats[0].value  += check_for_lines(display);
                push_next_block(display);
                if (is_game_over(display) == 1)
                    break;
            }
            fall = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0,"%s %d",text,d.stats[0].value);

            draw_board(display);
            draw_block(display, 1);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(block);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(drawingTimer);
    al_destroy_timer(fallTimer);
    al_destroy_timer(moveTimer);
    al_destroy_event_queue(queue);

    //gameOverA(display);
}

void gameOverA(struct Display *display){
	ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 30.0);
    must_init(drawingTimer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(400, 400);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(drawingTimer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    while(1){
		al_wait_for_event(queue, &event);

		switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            	redraw = true;
            	break;

            case ALLEGRO_EVENT_KEY_DOWN:
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

        if (redraw){
        	al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "GAME OVER");
        }

    }
}

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(drawingTimer);
    al_destroy_event_queue(queue);
}