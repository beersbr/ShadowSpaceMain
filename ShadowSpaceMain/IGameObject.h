#pragma once

#include <list>
#include <allegro5\allegro.h>


#include <windowsx.h>
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3d.h>

class IGameObject
{
public:
	IGameObject(void);
	virtual ~IGameObject(void);

	virtual int update(double timestamp) = 0;
	virtual int draw(LPDIRECT3DDEVICE9 dev) = 0;

	int instance_id() const;
	int object_type() const;

	// this is kinda here just for debugging
	static std::list<IGameObject*>* game_objects(void);

protected:
	int _object_type;
	long _instance_id;
	static long instance_id_inc;
	static std::list<IGameObject*> *_game_objects;
};

