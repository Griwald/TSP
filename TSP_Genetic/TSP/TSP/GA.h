#pragma once
#include"City.h"
#include "DNA.h"
#include <cmath> // pow


/* Fonction objectif :
 * Retourne la distance totale entre les villes parcourues dans l'ordre donn�
 */
int calcTotalDist(std::vector<City>& cities, std::vector<int>& order);


/* Calcule les valeurs de fitness */
void calcFitness(std::vector<DNA>& population);

/* Normalise les valeurs de fitness */
void normalizeFitness(std::vector<DNA>& population);

/* Cr�e la nouvelle g�n�ration � partir des meilleurs �lements de la pr�c�dente */
void nextGeneration(std::vector<DNA>& population);
