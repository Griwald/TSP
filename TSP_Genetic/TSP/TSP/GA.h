#pragma once
#include"City.h"
#include "DNA.h"
#include <cmath> // pow


/* Retourne la distance totale entre les villes parcourues dans l'ordre donne */
int calcTotalDist(std::vector<City>& cities, std::vector<int>& order);


/* Calcule les valeurs de fitness */
void calcFitness(std::vector<DNA>& population);

/* Normalise les valeurs de fitness */
void normalizeFitness(std::vector<DNA>& population);

/* Cree la nouvelle generation a partir des meilleurs elements de la precedente */
void nextGeneration(std::vector<DNA>& population);
