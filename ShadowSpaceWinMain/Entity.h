#pragma once

#include "Point.h"
#include "Vector.h"

class Entity
{
public:
	Entity(void);
	Entity(Entity &entity);

	Point center_pt();

	virtual ~Entity(void);

public:
	Point position;
	Vector accel;
	int width, height;

};

