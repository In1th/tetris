#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "board.c"

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

#define abs(x) x>0? x: -x

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

/* Structure containing all info about a signle block
 *
 * member: pattern[4][4] - 4x4 array containing location of single block pieces in bits {0, 1}
 * member: r,g,b - contains a value of block's color in RGB
 * member: x,y - contains x and y coodrinates of the upper-left corner of the block
 *
 */


int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* drawingTimer = al_create_timer(1.0 / 30.0);
    must_init(drawingTimer, "timer");
    ALLEGRO_TIMER* fallTimer = al_create_timer(1.0);
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

    al_start_timer(drawingTimer);
    al_start_timer(fallTimer);

    unsigned char col[3] = {0,0,255};
    struct Block b = generate_block(4,1,col);

    
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                if (event.timer.source == fallTimer) fall = true;
                if (event.timer.source == drawingTimer) redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
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
    al_destroy_event_queue(queue);

    return 0;
}


