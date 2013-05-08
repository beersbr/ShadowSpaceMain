#include <allegro5\allegro5.h>
#include "InputHandler.h"

enum {PLAYING, QUITTING, CLEANUP, LOADING};

int main(int argc, char** argv)
{
	if(!al_init()) return false;
	if(!al_install_keyboard()) return false;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	ALLEGRO_DISPLAY *display = al_create_display(1280, 800);
	if(!display) return false;

	int gamestate = PLAYING;
	ALLEGRO_TIMER *timer = al_create_timer(1.0/60);
	al_start_timer(timer);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	InputHandler* input = InputHandler::Instance();

	const double TICKS_PER_SECOND = 45;
	const double dt = 1.0f/60.0f;
	const double MAX_FRAMESKIP = 5;

	double game_time = 0.0f;
	double offset = al_get_time();

	while(gamestate == PLAYING)
	{
		ALLEGRO_EVENT evt;
		while(al_get_next_event(event_queue, &evt))
		{
			switch(evt.type)
			{
			case ALLEGRO_EVENT_KEY_DOWN:
				input->setKey(evt.keyboard.keycode);
				break;
			case ALLEGRO_EVENT_KEY_UP:
				input->unsetKey(evt.keyboard.keycode);
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				gamestate = QUITTING;
				break;
			case ALLEGRO_EVENT_TIMER:
				game_time = evt.timer.count * dt;

				//update
				if(input->isKeyDown(ALLEGRO_KEY_ESCAPE)) gamestate = QUITTING;

				if(input->


				break;
			}
		}

		double interpolation = (al_get_time() - offset - game_time) / dt;
		
		//display

		

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();

	}

	al_destroy_display(display);

	return true;
}