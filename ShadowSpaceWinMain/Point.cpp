#include "Point.h"

Point::Point(void)
{
	x = y = z = 0;
}

Point::Point(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Point::Point(const Point &pt)
{
	x = pt.x;
	y = pt.y;
	z = pt.z;
}

Point::~Point(void)
{
	x = y = z = 0;
}

Point& Point::operator=(const Point &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return (*this);
}

Point Point::operator+(const Point &p) const
{
	Point new_point = (*this);
	return (new_point += p);
}

Point Point::operator+(const float scalar) const
{
	Point new_point = (*this);
	return (new_point += scalar);
}

Point Point::operator-(const Point&p) const
{
	Point new_point = (*this);
	return (new_point -= p);
}

Point Point::operator-(const float scalar) const
{
	Point new_point = (*this);
	return (new_point -= scalar);
}

Point Point::operator*(const Point& p) const
{
	Point new_point = (*this);
	return (new_point *= p);
}

Point Point::operator*(const float scalar) const
{
	Point new_point = (*this);
	return (new_point *= scalar);
}

Point Point::operator/(const Point& p) const
{
	Point new_point = (*this);
	return (new_point /= p);
}

Point Point::operator/(const float scalar) const
{
	Point new_point = (*this);
	return (new_point /= scalar);
}

Point& Point::operator+=(const Point &p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return (*this);
}

Point& Point::operator+=(const float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	return (*this);
}

Point& Point::operator-=(const Point &p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return (*this);
}

Point& Point::operator-=(const float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return (*this);
}

Point& Point::operator*=(const Point &p)
{
	x *= p.x;
	y *= p.y;
	z *= p.z;
	return (*this);
}

Point& Point::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return (*this);

}

Point& Point::operator/=(const Point &p)
{
	x /= p.x;
	y /= p.y;
	z /= p.z;
	return (*this);
}

Point& Point::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return (*this);
}

bool Point::operator==(const Point &p) const
{
	return (x == p.x && y == p.y && z == p.z);
}