#pragma once
#include <iostream> // std::ostream


/**
 *	Classe qui abstrait l'id�e d'une ville index�e plac�e sur un plan
 */
class City
{
public:
	/* Attributs */
	int index; // Num�ro d'identifiction
	int posX;  // Position sur la largeur
	int posY;  // Position sur la hauteur


	/* Constructeurs */
	City();
	City(int index, int x = 0, int y = 0);


	/* Retourne la distance au carr� entre deux villes
	 * On �vite le calcul de la racine pour gagner en vitesse d'ex�cution
	 */
	static int distSq(City& a, City& b);


	/* Red�finition de l'op�rateur d'affichage */
	friend std::ostream& operator<< (std::ostream& os, const City& city)
	{
		os << city.index << " : (" << city.posX << "," << city.posY << ")";
		return os;
	}
};
