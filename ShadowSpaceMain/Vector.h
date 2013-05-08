#pragma once

#include <cmath>
#include "Point.h"

class Vector : Point
{
public:
	Vector(void);
	Vector(double X, double Y);
	~Vector(void);

	double Length();
};

