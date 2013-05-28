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

	Vector DotProduct(const Vector &v);
	double operator*(const Vector &v) const;
	Vector operator*(double d);
	Vector rotate(Vector &axis, double angle);
	double cos_angle(const Vector &v) const;

	double length() const;
};

