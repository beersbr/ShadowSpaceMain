#pragma once	
#include "Utility.h"
#include "Entity.h"
#include "IGameObject.h"

class Player : public IGameObject, public Entity
{
public:
	Player(void);
	~Player(void);

	int Update(double timestamp);
	int Draw(LPDIRECT3DDEVICE9 dev);
	int InitGeometry(LPDIRECT3DDEVICE9 dev);

private:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	D3DXMATRIX playerIdentityMatrix;

private:
	float angle;

	LPD3DXMESH meshSpaceship;		// define the mesh pointer
	D3DMATERIAL9* material;			// define the material object
	DWORD numMaterials;				// stores the number of materials in the mesh
};