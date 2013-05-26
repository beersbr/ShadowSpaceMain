#include "Game.h"

Game::Game(void)
{
	State = NONE;
}


Game::~Game(void)
{
}

int Game::Setup(void)
{
	State = SETUP;

	return TRUE;
}

MSG Game::Start(void)
{
	State = RUNNING;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(State != QUITTING)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			break;

	}

	return msg;
}