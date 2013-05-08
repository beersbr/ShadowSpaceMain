#pragma once

class Point
{
public:
	Point(void);
	Point(const Point &pt);
	Point(double X, double Y);
	~Point(void);

	Point operator+(const Point &p) const;
	Point operator+(const double oper) const;
	Point operator-(const Point &p) const;
	Point operator-(const double oper) const;
	Point operator*(const Point &p) const;
	Point operator*(const double oper) const;
	Point operator/(const double oper) const;

	Point& operator=(const Point &p);

	Point& operator+=(const Point &p);
	Point& operator+=(const double oper);
	Point& operator-=(const Point &p);
	Point& operator-=(const double oper);
	Point& operator*=(const Point &p);
	Point& operator*=(const double oper);
	Point& operator/=(const double oper);

	bool operator==(const Point &p) const;

public:
	double x, y;
};