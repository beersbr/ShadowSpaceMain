#include "Utility.h"

HWND CreateDefaultWindow(HINSTANCE handle, unsigned int winWidth, unsigned int winHeight, LPCWSTR windowTitle, WinCallbackProc winProc )
{
	HWND hWnd;
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = winProc;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszClassName = L"MainWinClass";

	RegisterClassEx(&windowClass);

	hWnd = CreateWindowEx(NULL,
						  L"MainWinClass",
						  windowTitle,
						  WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_POPUP // fullscreen values
						  300,
						  300,
						  winWidth,
						  winHeight,
						  NULL, // no parent window
						  NULL, // no menus
						  handle,
						  NULL); // no multiple windows

	return hWnd;
}