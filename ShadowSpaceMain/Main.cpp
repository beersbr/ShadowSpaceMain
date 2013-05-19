#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_direct3d.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "HighResTimer.h"
#include "InputHandler.h"
#include "Particle.h"

enum {PLAYING, QUITTING, CLEANUP, LOADING};

int main(int argc, char** argv)
{
	if(!al_init()) return false;
	if(!al_init_primitives_addon()) return false;
	if(!al_install_keyboard()) return false;

	HighResTimer hrtimer;
	if(!hrtimer.startTimer()) return false;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	ALLEGRO_DISPLAY *display = al_create_display(1280, 800);
	if(!display) return false;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("fonts\\pirulen.ttf", 12, 0);

	if(!font) return false;

	int gamestate = PLAYING;
	ALLEGRO_TIMER *timer = al_create_timer(1.0f/60.0f);
	al_start_timer(timer);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	InputHandler* input = InputHandler::Instance();

	Particle *p = new Particle();
	p->accel.x = 1.0f;
	p->position.x = 0.0f;
	p->position.y = 400.0f;

	double start_time = hrtimer.getMilliseconds();
	double current_time = hrtimer.getMilliseconds();
	const double dt = 1.0f/60.0f;
	double t = 0.0f;

	while(gamestate == PLAYING)
	{
		double new_time = hrtimer.getMilliseconds();
		double frame_time = new_time - current_time;
		current_time = new_time;

		while(frame_time > 0.0f)
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
					break;
				}
			}

			const float delta_time = min(frame_time, dt);


			//p->update();

			frame_time -= delta_time;
			t += delta_time;


		}

		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_draw_text(font, al_map_rgb(255, 255, 255), 350, 10, ALLEGRO_ALIGN_LEFT, "Allegro 5 Rocks!");

		al_draw_filled_circle(100, 100, 100, al_map_rgb(255, 255, 255));
		al_flip_display();
	}

	al_destroy_display(display);

	return true;
}