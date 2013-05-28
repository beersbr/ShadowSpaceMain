#include "Player.h"

Player::Player(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 1.0f;



}

Player::~Player(void)
{
}

int Player::Update(double timestamp)
{
	return 0;
}

int Player::Draw(LPDIRECT3DDEVICE9 dev)
{
	dev->SetFVF(FVF_DIFFUSE);

	dev->SetTransform(D3DTS_WORLD, &playerIdentityMatrix);
    dev->SetStreamSource(0, vertexBuffer, 0, sizeof(XYZ_DIFFUSE));
	dev->SetIndices(indexBuffer);
    dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 16);

	return 0;
}

int Player::InitGeometry(LPDIRECT3DDEVICE9 dev)
{
	XYZ_DIFFUSE verts[] = {
		{ -3.0f,  3.0f, -3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 0
		{  3.0f,  3.0f, -3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 1
		{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 2
		{  3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 3
												  
		{ -3.0f,  3.0f,  3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 4
		{  3.0f,  3.0f,  3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 5
		{ -3.0f, -3.0f,  3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 6
		{  3.0f, -3.0f,  3.0f, D3DCOLOR_XRGB(255, 128, 255) }, // 7
	};

	short index[] = {
		0, 1, 2,
		2, 1, 3,
		4, 0, 6,
		6, 0, 2,
		7, 5, 6,
		6, 5, 4,
		3, 1, 7,
		7, 1, 5,
		4, 5, 0,
		0, 5, 1,
		3, 7, 2,
		2, 7, 6
	};

	dev->CreateVertexBuffer(8*sizeof(XYZ_DIFFUSE),
                               0,
                               FVF_DIFFUSE,
                               D3DPOOL_MANAGED,
                               &vertexBuffer,
                               NULL);

	void *pVoid = NULL;
	vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, verts, sizeof(verts));
    vertexBuffer->Unlock();

	dev->CreateIndexBuffer(32*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, index, sizeof(index));
    indexBuffer->Unlock();

	D3DXMatrixIdentity(&playerIdentityMatrix);

	return 0;
}
