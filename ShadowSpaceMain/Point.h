#pragma once

class Point
{
public:
	Point(void);
	Point(Point &pt);
	Point(double X, double Y);
	~Point(void);

public:
	double x, y;
};