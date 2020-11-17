#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#define BOARD_HEIGHT 22
#define BOARD_WIDTH 14

//$(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void drawBoard(int x, int y, ALLEGRO_BITMAP* bm){

 int i,j;

 for (i = 0; i < BOARD_HEIGHT; i++){
    for (j = 0; j < BOARD_WIDTH; j++){
        if ((BOARD_HEIGHT-1 == i) || (i == 0) || (j == 0) || (BOARD_WIDTH-1 == j) ){
            al_draw_bitmap(bm, (x + 16*j), (y + 16*i), 0);
        }
    }
 }

}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

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
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

            drawBoard(100,100, block);
            //al_draw_bitmap(block, 100, 100, 0);
            //al_draw_bitmap(block, 116, 100, 0);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(block);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}