#pragma once
#include <vector> // std::vector


/**
 *	Classe qui structure un ordre de passage à travers les villes 
 *	et sa valeur de fitness associée
 */
class DNA
{
public:
	/* Attributs */
	std::vector<int> order; // Structure qui contient l'ordre de passage
	double fitness;			// Valeur de fitness associée à l'ordre


	/* Constructeurs */
	DNA();
	DNA(std::vector<int> order);
};
