#pragma once
#include <iostream> // std::ostream


/**
 *	Classe qui abstrait l'idée d'une ville indexée placée sur un plan
 */
class City
{
public:
	/* Attributs */
	int index; // Numéro d'identifiction
	int posX;  // Position sur la largeur
	int posY;  // Position sur la hauteur


	/* Constructeurs */
	City();
	City(int index, int x = 0, int y = 0);


	/* Retourne la distance au carré entre deux villes
	 * On évite le calcul de la racine pour gagner en vitesse d'exécution
	 */
	static int distSq(City& a, City& b);


	/* Redéfinition de l'opérateur d'affichage */
	friend std::ostream& operator<< (std::ostream& os, const City& city)
	{
		os << city.index << " : (" << city.posX << "," << city.posY << ")";
		return os;
	}
};
