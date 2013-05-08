#pragma once

class Point
{
public:
	Point(void);
	Point(const Point &pt);
	Point(double X, double Y);
	~Point(void);

	Point operator+(const Point &p) const;
	Point operator+(const double scalar) const;
	Point operator-(const Point &p) const;
	Point operator-(const double scalar) const;
	Point operator*(const Point &p) const;
	Point operator*(const double scalar) const;
	Point operator/(const Point &p) const;
	Point operator/(const double scalar) const;

	Point& operator=(const Point &p);

	Point& operator+=(const Point &p);
	Point& operator+=(const double scalar);
	Point& operator-=(const Point &p);
	Point& operator-=(const double scalar);
	Point& operator*=(const Point &p);
	Point& operator*=(const double scalar);
	Point& operator/=(const Point &p);
	Point& operator/=(const double scalar);

	bool operator==(const Point &p) const;

public:
	double x, y;
};