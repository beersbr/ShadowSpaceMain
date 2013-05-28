#pragma once

class Point
{
public:
	Point(void);
	Point(const Point &pt);
	Point(float X, float Y, float Z);
	~Point(void);

	Point& operator=(const Point &p);

	Point operator+(const Point &p) const;
	Point operator+(const float scalar) const;
	Point operator-(const Point &p) const;
	Point operator-(const float scalar) const;
	Point operator*(const Point &p) const;
	Point operator*(const float scalar) const;
	Point operator/(const Point &p) const;
	Point operator/(const float scalar) const;

	Point& operator+=(const Point &p);
	Point& operator+=(const float scalar);
	Point& operator-=(const Point &p);
	Point& operator-=(const float scalar);
	Point& operator*=(const Point &p);
	Point& operator*=(const float scalar);
	Point& operator/=(const Point &p);
	Point& operator/=(const float scalar);

	bool operator==(const Point &p) const;

public:
	float x, y, z;
};