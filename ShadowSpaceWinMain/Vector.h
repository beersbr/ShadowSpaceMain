#pragma once

#include <cmath>

#include "Point.h"

class Vector : public Point
{
public:
	Vector(void);
	Vector(double X, double Y, double Z);
	Vector(const Vector &v);
	Vector(const Point &p);
	~Vector(void);

	Vector& operator*(const Vector &v) const;
	Vector& operator*(const double d);
	Vector rotate(const Vector &axis, double angle);
	double cos_angle(const Vector &v) const;

	double length() const;
};

