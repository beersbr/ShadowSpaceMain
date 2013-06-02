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
        dev->SetMaterial(&material[i]);			// set the material for the subset
        meshSpaceship->DrawSubset(i);			// draw the subset
    }

	return 0;
}

int Player::InitGeometry(LPDIRECT3DDEVICE9 dev)
{

	LPD3DXBUFFER bufShipMaterial;
    D3DXLoadMeshFromX(L"models\\ship2.x",    // load this file
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

	D3DXMatrixIdentity(&playerIdentityMatrix);

	return 0;
}
