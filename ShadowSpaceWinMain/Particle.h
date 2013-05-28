#pragma once

#include "Entity.h"
#include "IGameObject.h"

#include <list>
#include <forward_list>
#include <d3d9.h>

class Particle : public Entity, IGameObject
{
public:
	Particle(void);
	~Particle(void);

	int Update(double timestamp);
	int Draw();

public:
	int timeToLive;
	double direction;

private:
	int born;
	static std::list<Particle*> *particles;
	std::forward_list<Entity*> *entities;
};

