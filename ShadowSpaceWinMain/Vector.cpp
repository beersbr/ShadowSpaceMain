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

Vector& Vector::operator*(const Vector &v) const
{
    double a = (y * v.z) - (z * v.y);
    double b = (z * v.x) - (x * v.z);
    double c = (x * v.y) - (y * v.x);

    return Vector(a, b, c);
}

Vector& Vector::operator*(const double d)
{
	(*this).x *= d;
	(*this).y *= d;
	(*this).z *= d;
	return *this;
}

Vector Vector::rotate(const Vector &axis, double angle)
{
	Vector t = (*this);
	return ((t - axis * (axis * t)) * cos(angle)) + (((axis * t) * sin(angle))) + (axis * (axis * t));
}

double Vector::cos_angle(const Vector &v) const
{
	return 0;
}

double Vector::length() const
{
	return sqrt(x*x + y*y);
}