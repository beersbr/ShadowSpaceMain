#include "Point.h"

Point::Point(void)
{
	x = y = 0;
}

Point::Point(double X, double Y)
{
	x = X;
	y = Y;
}

Point::Point(const Point &pt)
{
	x = pt.x;
	y = pt.y;
}

Point::~Point(void)
{
	x = y = 0;
}

Point Point::operator+(const Point &p) const
{
	Point new_point = (*this);
	return (new_point += p);
}

Point Point::operator+(const double scalar) const
{
	Point new_point = (*this);
	return (new_point += scalar);
}

Point Point::operator-(const Point&p) const
{
	Point new_point = (*this);
	return (new_point -= p);
}

Point Point::operator-(const double scalar) const
{
	Point new_point = (*this);
	return (new_point -= scalar);
}

Point Point::operator*(const Point& p) const
{
	Point new_point = (*this);
	return (new_point *= p);
}

Point Point::operator*(const double scalar) const
{
	Point new_point = (*this);
	return (new_point *= scalar);
}

Point Point::operator/(const Point& p) const
{
	Point new_point = (*this);
	return (new_point /= p);
}

Point Point::operator/(const double scalar) const
{

}
