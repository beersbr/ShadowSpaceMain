#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>

enum{
	NONE,
	SETUP,
	RUNNING,
	QUITTING,
	LOADING,
	CLEANUP
};

class Game
{
public:
	Game(void);
	~Game(void);

	int Setup(HWND windowHandle);
	MSG Start(void);

	int Render(void);
	int Update(void);

public:
	int State;
	LPDIRECT3D9 d3d9Interface;
	LPDIRECT3DDEVICE9 d3dDevice;

};

