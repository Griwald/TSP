#pragma once
#include <vector>    // std::vector


/**
 *	Classe qui structure un ordre de passage � travers les villes 
 *	et sa valeur de fitness associ�e
 */
class DNA
{
public:
	/* Attributs */
	std::vector<int> order; // Structure qui contient l'ordre de passage
	double fitness;			// Valeur de fitness associee a l'ordre


	/* Constructeurs */
	DNA();
	DNA(std::vector<int> order);
};
