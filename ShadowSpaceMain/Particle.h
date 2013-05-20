#pragma once

#include <list>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "Entity.h"
#include "IGameObject.h"

#include <list>

class Particle : public Entity, IGameObject
{
public:
	Particle(void);
	~Particle(void);

	int update(double timestamp);
	int draw(LPDIRECT3DDEVICE9 dev);

public:
	int time_to_live;
	double direction;
	ALLEGRO_COLOR color;

	static std::list<Particle *> particles;

private:
	int born;
	static std::list<Particle*> *particles;
};

