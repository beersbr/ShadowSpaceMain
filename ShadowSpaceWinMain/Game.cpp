#include "Game.h"

Game::Game(void)
{
	State = NONE;
	inputHandler = InputHandler::Instance();

	index = 0;
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
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = GameSettings::WINDOW_WIDTH;
	d3dpp.BackBufferWidth = GameSettings::WINDOW_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3d9Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, 
		windowHandle, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&d3dpp, 
		&d3dDevice);

	d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE); // turn off 3d lighting
	d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	gridSize = 10;

	cameraPosition.z = -20.0f;
	cameraPosition.y = 5.0f;
	cameraLookatPosition.y = 5.0f;
	cameraPolePosition.y = 5.0f;

	D3DXCreateFont(d3dDevice,    // the D3D Device
                   16,    // font height of 30
                   0,    // default font width
                   FW_NORMAL,    // font weight
                   1,    // not using MipLevels
                   false,    // italic font
                   DEFAULT_CHARSET,    // default character set
                   OUT_DEFAULT_PRECIS,    // default OutputPrecision,
                   DEFAULT_QUALITY,    // default Quality
                   DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
                   L"Arial",    // use Facename Arial
                   &dxfont);    // the font object


	player = new Player();
	hrTimer = new HighResTimer();
	moveCamera = true;
	return TRUE;
}

MSG Game::Start(void)
{
	State = RUNNING;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	XYZ_DIFFUSE vertices[] = {
		{  3.0f,  -3.0f,  1.0f, D3DCOLOR_ARGB(255, 160, 0, 160) },
		{  0.0f,   3.0f,  1.0f, D3DCOLOR_ARGB(255, 160, 0, 160) },
		{ -3.0f,  -3.0f,  1.0f, D3DCOLOR_ARGB(255, 160, 0, 160) },
	};

	vertexBuffer = NULL;
	d3dDevice->CreateVertexBuffer(3*sizeof(XYZ_DIFFUSE), 0, FVF_DIFFUSE, D3DPOOL_MANAGED, &vertexBuffer, NULL);

	void* pVoid;    // a void pointer

    vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    vertexBuffer->Unlock();

	InitDebugGrid();
	InitCameraPole();

	player->InitGeometry(d3dDevice);

	hrTimer->startTimer();
	offset = hrTimer->getMilliseconds();
	fps = 0;
	updates = 0;

	double updateInterval = 1000/60.0f;
	elapsedTime = 0.0f;
	double lastTime = hrTimer->getMilliseconds();
	double currentTime = hrTimer->getMilliseconds();
	double counter = 0.0;


	while(State != QUITTING)
	{
		lastTime = currentTime;
		currentTime = hrTimer->getMilliseconds();
		elapsedTime = currentTime - lastTime;

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			State = QUITTING;

		counter += elapsedTime;
		if(counter > updateInterval)
		{
			updates += 1;
			//counter = counter - updateInterval;
			Update(counter);
			counter = 0.0f;
			inputHandler->ClearStates();
		}

		Render();
	}

	Cleanup();

	return msg;
}

int Game::Render(void)
{
	fps += 1;

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0F, 0);
	d3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();
	d3dDevice->SetFVF(FVF_DIFFUSE);
	
    // SET UP THE PIPELINE

    D3DXMATRIX matView;    // the view transform matrix
    D3DXMatrixLookAtLH(&matView, 
		&D3DXVECTOR3 (cameraPosition.x, cameraPosition.y, cameraPosition.z),    // the camera position
		&D3DXVECTOR3 (cameraLookatPosition.x, cameraLookatPosition.y, cameraLookatPosition.z),    // the look-at position
        &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

    d3dDevice->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),    // the horizontal field of view
                               (FLOAT)GameSettings::WINDOW_WIDTH / (FLOAT)GameSettings::WINDOW_HEIGHT, // aspect ratio
                               1.0f,    // the near view-plane
                               100.0f);    // the far view-plane

    d3dDevice->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
	RenderDebugGrid();
	player->Draw(d3dDevice);
	RenderCameraPole();

	static RECT textbox; SetRect(&textbox, 0, 0, 800, 200); 

	char output[100];
	memset(output, '\0', 100);
	sprintf(output, "X: %5f Y: %5f  Z: %5f                 ", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    // draw the Hello World text
    dxfont->DrawTextA(NULL,
                      output,
                      strlen(output),
                      &textbox,
                      DT_LEFT | DT_VCENTER,
                      D3DCOLOR_ARGB(255, 255, 0, 255));

	SetRect(&textbox, 0, 200, 800, 400);

	sprintf(output, "fps: %5f", fps/((hrTimer->getMilliseconds() - offset)/1000));

    // draw the Hello World text
    dxfont->DrawTextA(NULL,
                      output,
                      strlen(output),
                      &textbox,
					  DT_LEFT | DT_VCENTER,
                      D3DCOLOR_ARGB(255, 255, 0, 255));

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);

	SetRect(&textbox, 0, 400, 800, 600);
	sprintf(output, "updates: %5f", updates/((hrTimer->getMilliseconds() - offset)/1000));

    // draw the Hello World text
    dxfont->DrawTextA(NULL,
                      output,
                      strlen(output),
                      &textbox,
					  DT_LEFT | DT_VCENTER,
                      D3DCOLOR_ARGB(255, 255, 0, 255));

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}

int Game::Update(double elapsedTime)
{
	if(inputHandler->IsKeyDown(VK_ESCAPE))
		State = QUITTING;

	player->Update(elapsedTime);

	if(inputHandler->IsKeyPressed('C'))
	{
		moveCamera = !moveCamera;
	}

	if(moveCamera)
	{
		UpdateCamera();
	}
	
	return TRUE;
}

int Game::Cleanup(void)
{
	State = CLEANUP;

	vertexBuffer->Release();
	d3dDevice->Release();
	d3d9Interface->Release();

	return TRUE;
}

int Game::RenderDebugGrid(void)
{
    d3dDevice->SetFVF(FVF_DIFFUSE);
    d3dDevice->SetTransform(D3DTS_WORLD, &gridIdentityMatrix);
    d3dDevice->SetStreamSource(0, debugGridBuffer, 0, sizeof(XYZ_DIFFUSE));
    d3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, gridSize * 4 + 2);
    return TRUE;
}

int Game::InitDebugGrid(void)
{
	gridSize = 10;

    d3dDevice->CreateVertexBuffer(sizeof(XYZ_DIFFUSE) * gridSize * 9,
                                0,
                                FVF_DIFFUSE,
                                D3DPOOL_MANAGED,
                                &debugGridBuffer,
                                0);

    XYZ_DIFFUSE* pGridData = NULL;
    debugGridBuffer->Lock(0, 0, (void**)&pGridData, 0);

    int index = 0;
    for(; index <= gridSize * 4 + 1; index++)
    {
        pGridData[index].x = (index % 2) ? gridSize : -gridSize;
        pGridData[index].y = 0.0f;
        pGridData[index].z = index / 2 - gridSize;
        pGridData[index].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
    }

    for(; index <= gridSize * 8 + 4; index++)
    {
        static int half = index;
        pGridData[index].x = (index - half) / 2 - gridSize;
        pGridData[index].y = 0.0f;
        pGridData[index].z = (index % 2) ? -gridSize : gridSize;
		pGridData[index].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
    }

    debugGridBuffer->Unlock();
    D3DXMatrixIdentity(&gridIdentityMatrix);
	return TRUE;
}

int Game::RenderCameraPole(void)
{
	d3dDevice->SetFVF(FVF_DIFFUSE);
	D3DXMATRIX m = UpdateCameraPole();
	d3dDevice->SetTransform(D3DTS_WORLD, &(cameraPoleIdentityMatrix * m));
	d3dDevice->SetStreamSource(0, cameraPoleBuffer, 0, sizeof(XYZ_DIFFUSE));
	d3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	return 0;
}

D3DXMATRIX Game::UpdateCameraPole(void)
{
	D3DXMATRIX translateToCamera;
	Vector d = cameraLookatPosition - cameraPolePosition;
	cameraPolePosition += d;
	D3DXMatrixTranslation(&translateToCamera, cameraPolePosition.x, cameraPolePosition.y, cameraPolePosition.z);
	return translateToCamera;
}

int Game::InitCameraPole(void)
{
	d3dDevice->CreateVertexBuffer(sizeof(XYZ_DIFFUSE) * 2,
		0,
		FVF_DIFFUSE,
		D3DPOOL_MANAGED,
		&cameraPoleBuffer,
		0);

	XYZ_DIFFUSE cameraVertices[] = { 
		{  0.0f,  2.0f,  0.0f, D3DCOLOR_XRGB(255, 0, 0) },
		{  0.0f, -2.0f,  0.0f, D3DCOLOR_XRGB(255, 0, 0) },
	};

	VOID *pVoid;
	cameraPoleBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, cameraVertices, sizeof(cameraVertices));
	cameraPoleBuffer->Unlock();
	D3DXMatrixIdentity(&cameraPoleIdentityMatrix);
	return 0;
}

int Game::UpdateCamera(void)
{
	if(inputHandler->IsKeyDown('D'))
	{
		Vector t = cameraLookatPosition - cameraPosition;

		float x = t.x;
		float z = t.z;

		float len = sqrt(x*x + z*z);
		x = x/len;
		z = z/len;

		cameraPosition.x += z*0.1f;
		cameraLookatPosition.x += z*0.1f;
		cameraPosition.z += x*0.1f*-1;
		cameraLookatPosition.z += x*0.1f*-1;
	}
	if(inputHandler->IsKeyDown('A'))
	{
		Vector t = cameraLookatPosition - cameraPosition;

		float x = t.x;
		float z = t.z;

		float len = sqrt(x*x + z*z);
		x = x/len;
		z = z/len;

		cameraPosition.x += z*0.1f*-1;
		cameraLookatPosition.x += z*0.1f*-1;
		cameraPosition.z += x*0.1f;
		cameraLookatPosition.z += x*0.1f;
	}
	if(inputHandler->IsKeyDown('W'))
	{
		Vector t = cameraLookatPosition - cameraPosition;
		t = t.toUnit();
		t *= 0.1f;
		cameraPosition += t;
		cameraLookatPosition += t;
	}
	if(inputHandler->IsKeyDown('S'))
	{
		Vector t = cameraLookatPosition - cameraPosition;
		t = t.inverse();
		t = t.toUnit();
		t *= 0.1f;
		cameraPosition += t;
		cameraLookatPosition += t;
	}

	if(inputHandler->IsKeyDown(VK_UP))
	{
		cameraLookatPosition.y += 0.2f; 
	}
	if(inputHandler->IsKeyDown(VK_DOWN))
	{
		cameraLookatPosition.y -= 0.2f;
	}
	if(inputHandler->IsKeyDown(VK_LEFT))
	{
		Vector C = cameraLookatPosition - cameraPosition;
		Vector d = C.rotate(Vector(0.0f, 1.0f, 0.0f), D3DXToRadian(-1.0f));
		d = d - C;
		cameraLookatPosition.x += d.x;
		cameraLookatPosition.z += d.z;
	}
	if(inputHandler->IsKeyDown(VK_RIGHT))
	{
		Vector C = cameraLookatPosition - cameraPosition;
		Vector d = C.rotate(Vector(0.0f, 1.0f, 0.0f), D3DXToRadian(1.0f));
		d = d - C;
		cameraLookatPosition.x += d.x;
		cameraLookatPosition.z += d.z;
	}

	GetCursorPos(&mousePos);
	//SetCursorPos(GameSettings::WINDOW_WIDTH / 2, GameSettings::WINDOW_HEIGHT / 2);

	mousePos.x -= GameSettings::WINDOW_WIDTH / 2;
	mousePos.y -= GameSettings::WINDOW_HEIGHT / 2;

	//if(mousePos.x != 0)
	if(false)
	{
		Vector C = cameraLookatPosition - cameraPosition;
		Vector d = C.rotate(Vector(0.0f, 1.0f, 0.0f), D3DXToDegree(mousePos.x * 0.00001f));

		cameraLookatPosition.x = d.x;
		cameraLookatPosition.z = d.z;

		//Vector t = cameraPosition - cameraLookatPosition;
		//float x = t.x;
		//float z = t.z;
		//float len = sqrt(x*x + z*z);
		//x = x/len;
		//z = z/len;

		//int mod = (mousePos.x < 0 ? -1 : 1);

		//cameraLookatPosition.x -= z*0.1f * mod * (mousePos.x*mousePos.x/2)*0.1f;
		//cameraLookatPosition.z -= x*0.1f * mod*-1 * (mousePos.x*mousePos.x/2)*0.1f;


		cameraLookatPosition.y -= mousePos.y*0.1f;
	}

	return 0;
}