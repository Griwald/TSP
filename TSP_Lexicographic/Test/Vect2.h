#pragma once
#include <iostream>

class Vect2
{
public:
	int x;
	int y;

	Vect2(int x = 0, int y = 0);
	~Vect2();

	static int distSq(Vect2& u, Vect2& v);

	friend std::ostream& operator<< (std::ostream& os, const Vect2& v)
	{
		os << "Vect2 : (" << v.x << "," << v.y << ")";
		return os;
	}
};

