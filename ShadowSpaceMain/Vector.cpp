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

double Vector::Length()
{
	return sqrt(x*x + y*y);
}