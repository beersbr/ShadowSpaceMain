#pragma once

#include "SharedSettings.h"

#include <Windows.h>
#include <Windowsx.h>

typedef LRESULT (CALLBACK *WinCallbackProc)(HWND, unsigned int, WPARAM, LPARAM);

HWND CreateDefaultWindow(HINSTANCE handle, unsigned int winWidth, unsigned int winHeight, LPCWSTR windowTitle, WinCallbackProc winProc);