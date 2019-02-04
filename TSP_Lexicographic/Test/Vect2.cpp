#include "pch.h"
#include "Vect2.h"


Vect2::Vect2(int x_, int y_)
{
	x = x_;
	y = y_;
}


Vect2::~Vect2()
{
}

int Vect2::distSq(Vect2& u, Vect2& v)
{
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);
}
