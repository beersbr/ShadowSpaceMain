#pragma once

#include <list>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "Entity.h"
#include "IGameObject.h"

class Particle : public Entity, IGameObject
{
public:
	Particle(void);
	~Particle(void);

	int update(double timestamp);
	int draw(void);

public:
	int time_to_live;
	double direction;
	ALLEGRO_COLOR color;

private:
	int born;
	static std::list<Particle*> *particles;
};

