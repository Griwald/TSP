#include "pch.h"
#include "City.h"


City::City()
{
	index = 0;
	posX = 0;
	posY = 0;
}

City::City(int index_, int x_, int y_)
{
	index = index_;

	posX = x_;
	posY = y_;
}


int City::distSq(City& a, City& b)
{
	return (a.posX - b.posX) * (a.posX - b.posX) + (a.posY - b.posY) * (a.posY - b.posY);
}
