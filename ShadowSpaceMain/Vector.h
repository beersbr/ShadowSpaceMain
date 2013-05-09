#pragma once

#include <cmath>

#include "Point.h"

class Vector : Point
{
public:
	Vector(void);
	Vector(double X, double Y);
	~Vector(void);

	double operator*(const Vector &v) const;
	double cos_angle(const Vector &v) const;

	double length() const;
};

