#pragma once
#include <iostream>

class City
{
public:
	int index; // Numero d'identifiction
	int posX;  // Position sur la largeur
	int posY;  // Position sur la hauteur


	City(int index, int x = 0, int y = 0);


	static int distSq(City& a, City& b);

	friend std::ostream& operator<< (std::ostream& os, const City& city)
	{
		os << city.index << " : (" << city.posX << "," << city.posY << ")";
		return os;
	}
};

