#pragma once
#include"City.h"
#include "DNA.h"
#include <cmath> // pow


/* Fonction objectif :
 * Retourne la distance totale entre les villes parcourues dans l'ordre donné
 */
int calcTotalDist(std::vector<City>& cities, std::vector<int>& order);


/* Calcule les valeurs de fitness */
void calcFitness(std::vector<DNA>& population);

/* Normalise les valeurs de fitness */
void normalizeFitness(std::vector<DNA>& population);

/* Crée la nouvelle génération à partir des meilleurs élements de la précédente */
void nextGeneration(std::vector<DNA>& population);
