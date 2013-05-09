#include "Vector.h"


Vector::Vector(void) : Point()
{
}

Vector::Vector(double X, double Y) : Point(X, Y)
{
}

Vector::~Vector(void)
{
}

double Vector::operator*(const Vector &v) const
{
	return (x*v.x + y*v.y);
}

double Vector::cos_angle(const Vector &v) const
{
	double cos_omega = ((*this) * v)/((*this).length() * v.length());
	return cos_omega;
}

double Vector::length() const
{
	return sqrt(x*x + y*y);
}