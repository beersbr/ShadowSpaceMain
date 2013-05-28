#include "SharedSettings.h"
#include "Utility.h"
#include "Game.h"

#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK WinCallback(HWND, unsigned int, WPARAM, LPARAM);
Game *ShadowSpaceGame = NULL;

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	HWND hWnd = CreateDefaultWindow(hInstance, 
			GameSettings::WINDOW_WIDTH, 
			GameSettings::WINDOW_HEIGHT,
			GameSettings::TITLE,
			WinCallback);


	ShowWindow(hWnd, nCmdShow);

	ShadowSpaceGame = new Game();
	ShadowSpaceGame->Setup(hWnd);
	MSG ret = ShadowSpaceGame->Start();

	return ret.wParam;
}

LRESULT CALLBACK WinCallback(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		ShadowSpaceGame->inputHandler->SetKey(wParam);
		break;
	case WM_KEYUP:
		ShadowSpaceGame->inputHandler->UnSetKey(wParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}