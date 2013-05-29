#include "Player.h"

Player::Player(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 1.0f;

	angle = 0.0f;
}

Player::~Player(void)
{
}

int Player::Update(double timestamp)
{
	angle += 180.0f * timestamp/1000.0f;

	return 0;
}

int Player::Draw(LPDIRECT3DDEVICE9 dev)
{
	dev->SetFVF(FVF_DIFFUSE);

	D3DXMATRIX rotMatrix;

	D3DXMatrixRotationX(&rotMatrix, D3DXToRadian(angle));

	for(DWORD i = 0; i < numMaterials; i++)    // loop through each subset
    {
        dev->SetMaterial(&material[i]);    // set the material for the subset
        meshSpaceship->DrawSubset(i);    // draw the subset
    }

	//dev->SetTransform(D3DTS_WORLD, &(playerIdentityMatrix*rotMatrix));
 //   dev->SetStreamSource(0, vertexBuffer, 0, sizeof(XYZ_DIFFUSE));
	//dev->SetIndices(indexBuffer);
 //   dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 16);

	return 0;
}

int Player::InitGeometry(LPDIRECT3DDEVICE9 dev)
{

	LPD3DXBUFFER bufShipMaterial;
    D3DXLoadMeshFromX(L"models\\ship.x",    // load this file
                      D3DXMESH_SYSTEMMEM,    // load the mesh into system memory
                      dev,    // the Direct3D Device
                      NULL,    // we aren't using adjacency
                      &bufShipMaterial,    // put the materials here
                      NULL,    // we aren't using effect instances
                      &numMaterials,    // the number of materials in this model
                      &meshSpaceship);    // put the mesh here

    // retrieve the pointer to the buffer containing the material information
    D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)bufShipMaterial->GetBufferPointer();

    // create a new material buffer for each material in the mesh
    material = new D3DMATERIAL9[numMaterials];

    for(DWORD i = 0; i < numMaterials; i++)    // for each material...
    {
        material[i] = tempMaterials[i].MatD3D;    // get the material info
        material[i].Ambient = material[i].Diffuse;    // make ambient the same as diffuse
    }

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

	dev->CreateIndexBuffer(36*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);

	indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, index, sizeof(index));
    indexBuffer->Unlock();

	D3DXMatrixIdentity(&playerIdentityMatrix);

	return 0;
}
