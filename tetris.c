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

void must_init(bool test, const char *description){
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
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

    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    must_init(disp, "display");

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

    struct Display dis;
    dis.current_block = generate_block(new_color());
    dis.next_block = generate_block(new_color());
    setup_board(&dis);
    dis.board_x = 100;
    dis.board_y = 100;

    char lines = 0;
    
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (event.timer.source == fallTimer) fall = true;
                if (event.timer.source == moveTimer){
                    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)) {
                        if (detect_collision(&dis,-1,0) == 0)
                            dis.current_block.x--;
                    }
                    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT)) {
                        if (detect_collision(&dis,1,0) == 0)
                            dis.current_block.x++;
                    }
                }
                if (event.timer.source == drawingTimer) {
                    redraw = true;
                    
                    al_get_keyboard_state(&ks);

                    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)){
                        if (detect_collision(&dis,0,1) == 0){
                        fall = false;
                        dis.current_block.y++;
                        }
                        else {
                            place_block(&dis);
                            lines += check_for_lines(&dis);
                            push_next_block(&dis);
                        }
                    }  
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    reverse_with_collision(&dis);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_Z){
                    rotate_with_collision(&dis,0);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_X){
                    rotate_with_collision(&dis,1);
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
            if (detect_collision(&dis,0,1) == 0) 
                dis.current_block.y++;
            else {
                place_block(&dis);
                lines += check_for_lines(&dis);
                push_next_block(&dis);
                if (is_game_over(&dis) == 1)
                    break;
            }
            fall = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "LINES: %c",lines);

            draw_board(&dis);
            draw_block(&dis, 1);
            //al_draw_bitmap(block, 100, 100, 0);
            //al_draw_bitmap(block, 116, 100, 0);

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

    return 0;
}


