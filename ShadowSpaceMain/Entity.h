#pragma once

#include "Point.h"

class Entity
{
public:
	Entity(void);
	Entity(Entity &entity);

	Point center_pt();

	virtual ~Entity(void);

public:
	double x, y;
	double accel_x, accel_y;
	int width, height;

};

