// TSP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "City.h" // var: cities
#include "DNA.h"
#include "GA.h"
#include <iostream>  // std::cout 
#include <vector>	 // std::vector
#include <algorithm> // std::random_shuffle
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time
#include <chrono>	 // std::chrono::
#include <climits>   // UINT_MAX

using namespace std;


// Initialisation de la variable externe
vector<City> cities;


int main()
{
	const int width = 200;			// Largeur de l'espace de placement des villes
	const int height = 200;			// Hauteur de l'espace de placement des villes
	const int nbOfCities = 20;		// Nombre de villes placees dans l'espace
	const int nbOfPopulation = 500; // Taille de la population
	const int nbOfGeneration = 1;	// Nombre de generation

	vector<DNA> population; // Structure qui contient la population


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de generation aleatoire
	srand(time(NULL));


	// Création des villes
	vector<int> order(nbOfCities);
	for (int i = 0; i < nbOfCities; i++) {
		int posX = rand() % width;
		int posY = rand() % height;
		cities.push_back(City(i, posX, posY));

		// Ordre de parcours croissant
		order[i] = i;
	}

	// Initialisation de la meilleure distance de parcours et du meilleur ordre
	unsigned int bestDist = UINT_MAX;
	vector<int> bestOrder = order;

	// Creation de la population
	for (int i = 0; i < nbOfPopulation; i++) {
		// Ordre de parcours aleatoire pour la population
		vector<int> shuffleOrder(order);
		random_shuffle(shuffleOrder.begin(), shuffleOrder.end());

		// Initialisation de la population
		population.push_back(DNA(shuffleOrder));
	}


	// Affichage de la position des villes
	cout << "Position des villes :" << endl;
	for (City &city : cities) {
		cout << city << endl;
	}
	cout << endl;


	// ================================================================================
	// ALGORITHMES GENETIQUES 
	// ================================================================================ 

	// Début du chronometre
	auto start = chrono::system_clock::now();

	int count = 0;
	while (count != nbOfGeneration) {

		// Application des algorithmes genetiques
		calcFitness(population);
		normalizeFitness(population);
		nextGeneration(population);

		// Recherche du meilleur ordre de parcours
		for (int i = 0; i < population.size(); i++) {
			vector<int> currentOrder = population[i].order;
			int dist = calcTotalDist(cities, currentOrder);
			if (dist < bestDist) {
				bestDist = dist;
				bestOrder = currentOrder;
			}
		}

		count++;
	}


	// ================================================================================
	// AFFICHAGE DU RESULTAT 
	// ================================================================================ 

	cout << "Meilleur ordre de parcours :" << endl;
	for (int &index : bestOrder) {
		cout << index << " ";
	}
	cout << endl << endl;

	cout << "Distance parcourue pour cet ordre (au carre) : " << bestDist << endl;


	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Duree du programme : " << elapsed_seconds.count() << "s" << endl;


	return 0;
}
