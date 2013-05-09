#pragma once

#include <list>
#include "Entity.h"
#include "IGameObject.h"

class Particle : Entity, IGameObject
{
public:
	Particle(void);
	~Particle(void);

public:
	int time_to_live;
	double direction;
	ALLEGRO_COLOR color;

private:
	int born;
	static std::list<Particle*> *particles;
};

