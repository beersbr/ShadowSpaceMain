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

Point::Point(Point &pt)
{
	x = pt.x;
	y = pt.y;
}

Point::~Point(void)
{
	x = y = 0;
}
