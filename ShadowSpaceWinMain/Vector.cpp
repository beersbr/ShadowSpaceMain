#include "Vector.h"


Vector::Vector(void) : Point()
{
}

Vector::Vector(double X, double Y, double Z) : Point(X, Y, Z)
{
}

Vector::Vector(const Vector &v) : Point(v)
{

}

Vector::Vector(const Point &p) : Point(p)
{
}

Vector::~Vector(void)
{
}

 Vector Vector::DotProduct(const Vector &v)
{
    double a = (y * v.z) - (z * v.y);
    double b = (z * v.x) - (x * v.z);
    double c = (x * v.y) - (y * v.x);

    return Vector(a, b, c);
}

double Vector::operator*(const Vector &v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector Vector::operator*(const double d)
{
	return Vector(x*d, y*d, z*d);
}

Vector Vector::rotate(Vector &axis, double angle)
{
	Vector t = (*this);
	return ((t - axis * (axis * t)) * cos(angle)) + (axis.DotProduct(t) * sin(angle)) + (axis * (axis * t));
}

double Vector::cos_angle(const Vector &v) const
{
	return 0;
}

double Vector::length() const
{
	return sqrt(x*x + y*y);
}