#pragma once
template <class T>
class Point
{
public:
	Point(void)
	{
		x = y = 0;
	}

	Point(T X, T Y)
	{
		x = X;
		y = Y;
	}



	~Point(void);

public:
	T x;
	T y;
};

