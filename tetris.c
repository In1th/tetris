#include "board.c"

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 30.0);
    ALLEGRO_TIMER* fallTimer = al_create_timer(1.25);
    ALLEGRO_TIMER* moveTimer = al_create_timer(1.0 / 30.0);
    must_init(drawingTimer, "timer");
    must_init(fallTimer, "timer");



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

    bool done = false;
    bool redraw = true;
    bool fall = false;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);
    al_start_timer(moveTimer);

    unsigned char col[3] = {0,0,255};
    struct Block b = generate_block(randChar(0,6),randChar(0,2),col);

    
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (event.timer.source == fallTimer) fall = true;
                if (event.timer.source == drawingTimer) {
                    redraw = true;
                    
                    al_get_keyboard_state(&ks);

                    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)) 
                        b.x--;
                    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT)) 
                        b.x++;
                    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)){
                        fall = false;
                        b.y++;
                    }    
                }
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    reverse(&b);
                    break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_UP){
                    rotate(&b);
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
            b.y++;
            fall = false;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "TETRIS MODAFUKA!");

            draw_board(100,100, block);
            draw_block(100,100, b, block);
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


