#include "Game.h"

Game::Game(void)
{
	State = NONE;
}

Game::~Game(void)
{
}

int Game::Setup(HWND windowHandle)
{
	State = SETUP;
	d3d9Interface = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = windowHandle;

	d3d9Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, 
		windowHandle, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&d3dpp, 
		&d3dDevice);
	


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

		Update();
		Render();
	}

	return msg;
}

int Game::Render(void)
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0F, 0);

	d3dDevice->BeginScene();
	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}

int Game::Update(void)
{
	return TRUE;
}