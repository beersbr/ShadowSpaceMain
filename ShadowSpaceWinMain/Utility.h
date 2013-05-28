#pragma once

#include "SharedSettings.h"

#include <Windows.h>
#include <Windowsx.h>

#include <d3d9.h>

#define FVF_DIFFUSE_NORMAL_SPECULAR (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_SPECULAR)
#define FVF_DIFFUSE_NORMAL			(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL )
#define FVF_DIFFUSE					(D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct XYZ_DIFFUSE_NORMAL_SPECULAR
{
    FLOAT x, y, z;
    D3DCOLOR diffuse;
	D3DCOLOR ambient;
	D3DCOLOR specular;
};

struct XYZ_DIFFUSE_NORMAL
{
    FLOAT x, y, z;
    D3DCOLOR diffuse;
	D3DCOLOR ambient;
};

struct XYZ_DIFFUSE
{
    FLOAT x, y, z;
    D3DCOLOR diffuse;
};


typedef LRESULT (CALLBACK *WinCallbackProc)(HWND, unsigned int, WPARAM, LPARAM);

HWND CreateDefaultWindow(HINSTANCE handle, unsigned int winWidth, unsigned int winHeight, LPCWSTR windowTitle, WinCallbackProc winProc);