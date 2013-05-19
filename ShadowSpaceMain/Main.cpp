#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_direct3d.h>
#include <d3d9.h>
#include <d3d.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "HighResTimer.h"
#include "InputHandler.h"
#include "Particle.h"

enum {PLAYING, QUITTING, CLEANUP, LOADING};

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
    DWORD color;    // from the D3DFVF_DIFFUSE flag
};

int main(int argc, char** argv)
{
	if(!al_init()) return false;
	if(!al_init_primitives_addon()) return false;
	if(!al_install_keyboard()) return false;

	HighResTimer hrtimer;
	if(!hrtimer.startTimer()) return false;

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	//al_set_new_display_flags(ALLEGRO_DIRECT3D);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
	al_set_new_display_refresh_rate(60);
	ALLEGRO_DISPLAY *display = al_create_display(1280, 800);
	if(!display) return false;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("fonts\\00tt.ttf", 25, 0);

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
	double elapsed_time = 0.0f;
	double fps = 0;
	int frames = 0;
	double game_time = 0.0f;
	double end_time = hrtimer.getMilliseconds();

	LPDIRECT3DDEVICE9 device = al_get_d3d_device(display);

	CUSTOMVERTEX OurVertices[] =
	{
		{320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255),},
		{520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0),},
		{120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0),},
	};

	LPDIRECT3DVERTEXBUFFER9 v_buffer;
	device->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),
                           0,
                           CUSTOMFVF,
                           D3DPOOL_MANAGED,
                           &v_buffer,
                           NULL);

	 VOID* pVoid;
	 v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	 memcpy(pVoid, OurVertices, sizeof(OurVertices));
     v_buffer->Unlock();

	while(gamestate == PLAYING)
	{
		start_time = hrtimer.getMilliseconds();
		elapsed_time += t;

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

		if(elapsed_time > dt)
		{
			p->update(elapsed_time/1000.0f);
			elapsed_time = 0;
		}

		//fps = frames/(game_time);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		/*al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 10, ALLEGRO_ALIGN_LEFT, "%f", fps*1000.0f);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 50, ALLEGRO_ALIGN_LEFT, "%d", frames);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 90, ALLEGRO_ALIGN_LEFT, "%d", (int)game_time);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 350, 130, ALLEGRO_ALIGN_LEFT, "%f", frame_time);*/
		device->SetFVF(CUSTOMFVF);
		device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
		device->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		p->draw();
		al_flip_display();
		//frames += 1;

		end_time = hrtimer.getMilliseconds();
		t = (end_time - start_time);
	}

	al_destroy_display(display);

	return true;
}