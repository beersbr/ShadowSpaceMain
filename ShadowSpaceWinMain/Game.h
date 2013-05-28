#pragma once

#include "SharedSettings.h"
#include "Utility.h"
#include "InputHandler.h"
#include "Point.h"
#include "Vector.h"
#include "Player.h"

#include <cmath>
#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

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

	int Render();
	int Update(void);
	int Cleanup(void);

	int UpdateCamera(void);

public:
	int State;
	LPDIRECT3D9 d3d9Interface;
	LPDIRECT3DDEVICE9 d3dDevice;
	InputHandler* inputHandler;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

private:
	int RenderDebugGrid(void);
	int InitDebugGrid(void);

	int RenderCameraPole(void);
	D3DXMATRIX UpdateCameraPole(void);
	int InitCameraPole(void);

private:
	float index;

	LPDIRECT3DVERTEXBUFFER9 debugGridBuffer;
	D3DXMATRIX gridIdentityMatrix;
	int gridSize;

	LPDIRECT3DVERTEXBUFFER9 cameraPoleBuffer;
	D3DXMATRIX cameraPoleIdentityMatrix;

	Player *player;

	Vector cameraPosition;
	Vector cameraLookatPosition;

	Vector cameraPolePosition;

	POINT lastMousePos;
};

