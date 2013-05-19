#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_direct3d.h>
#include <windowsx.h>
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3d.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "HighResTimer.h"
#include "InputHandler.h"
#include "Particle.h"

enum {PLAYING, QUITTING, CLEANUP, LOADING};

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

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
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
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

	
	double angle = 100;
	double rot_per_sec = D3DXToRadian(40);


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
			angle += rot_per_sec*(elapsed_time/1000.0f);
			elapsed_time = 0;
		}

		//fps = frames/(game_time);

		/*al_clear_to_color(al_map_rgb(0, 0, 0));*/
		device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
		//device->BeginScene();

		device->SetFVF(CUSTOMFVF);
		
		D3DXMATRIX mat_rotate;
		D3DXMatrixRotationY(&mat_rotate, angle);
		device->SetTransform(D3DTS_WORLD, &mat_rotate);

		D3DXMATRIX mat_view; 
		D3DXMatrixLookAtLH(&mat_view,
                       &D3DXVECTOR3 (0.0f, 0.0f, 10.0f),    // the camera position
                       &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),    // the look-at position
                       &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

		device->SetTransform(D3DTS_VIEW, &mat_view);
		
		D3DXMATRIX matProjection;
		D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),    // the horizontal field of view
                               (FLOAT)1200 / (FLOAT)800, // aspect ratio
                               1.0f,    // the near view-plane
                               100.0f);    // the far view-plane

		device->SetTransform(D3DTS_PROJECTION, &matProjection);
		
		
		device->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		p->draw();
		//device->EndScene();

		/*device->Present(NULL, NULL, NULL, NULL);*/
		al_flip_display();
		//frames += 1;

		end_time = hrtimer.getMilliseconds();
		t = (end_time - start_time);
	}

	al_destroy_display(display);

	return true;
}