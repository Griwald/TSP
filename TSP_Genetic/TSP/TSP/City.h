#pragma once
#include <iostream> // std::ostream
#include <vector>   // std::vector


/**
 *	Classe qui abstrait l'idee d'une ville indexee placee sur un plan
 */
class City
{
public:
	/* Attributs */
	int index; // Numero d'identifiction
	int posX;  // Position sur la largeur
	int posY;  // Position sur la hauteur


	/* Constructeurs */
	City();
	City(int index, int x = 0, int y = 0);


	/* Retourne la distance au carre entre deux villes 
	 * On évite le calcul de la racine pour gagner en vitesse d'execution 
	 */
	static int distSq(City& a, City& b);


	/* Redéfinition de l'operateur d'affichage */
	friend std::ostream& operator<< (std::ostream& os, const City& city)
	{
		os << city.index << " : (" << city.posX << "," << city.posY << ")";
		return os;
	}
};


// Structure qui contient les villes
extern std::vector<City> cities;