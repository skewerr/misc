#include <allegro5/allegro.h>

static const int FPS = 60;
static const int SW  = 640;
static const int SH  = 480;

ALLEGRO_EVENT_QUEUE *evqueue;
ALLEGRO_DISPLAY     *display;
ALLEGRO_TIMER       *uptimer;

int
main(void)
{
	al_init();
	al_install_keyboard();

	display = al_create_display(SW, SH);
	uptimer = al_create_timer(1.0/FPS);
	evqueue = al_create_event_queue();

	al_start_timer(uptimer);

	/* call "scene" handlers */

	al_destroy_display(display);
	al_destroy_timer(uptimer);
	al_destroy_event_queue(evqueue);

	return 0;
}
