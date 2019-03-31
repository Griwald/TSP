#pragma once
#include"City.h"
#include "DNA.h"
#include "pch.h"
//#include <vector>
//#include <cmath> // pow

using namespace std;

/* Fonction objectif :
 * Retourne la distance totale entre les villes parcourues dans l'ordre donn�
 */
int calcTotalDist(std::vector<City>& cities, std::vector<int>& order);


/* Calcule les valeurs de fitness */
void calculateFitness(std::vector<DNA>& population, vector<City>& cities);

/* Normalise les valeurs de fitness */
void normalizeFitness(std::vector<DNA>& population);

/* Cr�e la nouvelle g�n�ration � partir des meilleurs �lements de la pr�c�dente */
void nextGeneration(std::vector<DNA>& population);
