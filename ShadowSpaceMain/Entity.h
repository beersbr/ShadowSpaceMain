#pragma once

class Entity
{
public:
	Entity(void);
	Entity(Entity &entity);

	double center_x();
	double center_y();
	Point<double> center_pt();

	virtual ~Entity(void);

public:
	double x, y;
	double accel_x, accel_y;
	int width, height;

private:
	double center_x, center_y;
};

