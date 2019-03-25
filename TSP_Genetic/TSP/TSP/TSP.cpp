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

/* Fonction objectif :
 * Retourne la distance totale entre les villes parcourues dans l'ordre donné
 */
int calcTotalDistlocal(vector<City>& cities, vector<int>& order)
{
	int totalDist = 0;
	for (int i = 0; i < order.size() - 1; i++) {
		City cityA = cities[order[i]];
		City cityB = cities[order[i + 1]];
		totalDist += City::distSq(cityA, cityB);
	}
	return totalDist;
}


int main()
{
	const int width = 200;			 // Largeur de l'espace de placement des villes
	const int height = 200;			 // Hauteur de l'espace de placement des villes
	const int nbOfCities = 7;		 // Nombre de villes placées dans l'espace
	const int nbOfPopulation = 200;	 // Taille de la population
	const int nbOfGenerations = 50;	 // Nombre de générations

	vector<DNA> population; // Structure qui contient la population


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de génération aléatoire
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

	// Création de la population
	for (int i = 0; i < nbOfPopulation; i++) {
		// Ordre de parcours aléatoire pour la population
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

	// Début du chronomètre
	auto start = chrono::system_clock::now();

	int count = 0;
	while (count != nbOfGenerations) {

		// Application des algorithmes génétiques
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
				cout << "now" << endl;
			}
		}
		cout << count << endl;

		count++;
	}

	// Fin du chronomètre
	auto end = chrono::system_clock::now();


	// ================================================================================
	// AFFICHAGE DU RESULTAT 
	// ================================================================================ 

	// Affichage du meilleur ordre de parcours
	cout << "Meilleur ordre de parcours :" << endl;
	for (int &index : bestOrder) {
		cout << index << " ";
	}
	cout << endl << endl;

	// Affichage de la meilleure distance
	cout << "Distance parcourue pour cet ordre (au carre) : " << bestDist << endl;

	// Affichage de la durée d'exécution
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Duree du programme : " << elapsed_seconds.count() << "s" << endl;



	cout << "//////////////////////////////////////////////////////////" << endl;




	// Création des villes
	for (int i = 0; i < nbOfCities; i++) {

		// Remplissage de la stucture d'ordre de parcours
		order[i] = i;
	}

	// Initialisation de la meilleure distance de parcours et du meilleur ordre
	bestDist = UINT_MAX;
	bestOrder = order;

	// Affichage de la position des villes
	cout << "Position des villes :" << endl;
	for (City &city : cities) {
		cout << city << endl;
	}
	cout << endl;


	// ================================================================================
	// PARCOURS DU GRAPHE 
	// ================================================================================ 

	// Début du chronomètre
	start = chrono::system_clock::now();

	bool finished = false;
	while (!finished) {

		// Astuce pour ne pas considérer les permutations qui donnent un ordre "inverse"
		// ex: ne pas considérer {3,2,1} qui traite le même chemin que {1,2,3}
		if (order[0] < order[order.size() - 1]) {
			// On calcule la distance de parcours total avec l'ordre actuel
			int dist = calcTotalDistlocal(cities, order);
			// Si on trouve une meilleure distance de parcours, on l'enregistre ainsi que son ordre de parcours associé
			if (dist < bestDist) {
				bestDist = dist;
				bestOrder = order;
			}
		}


		// ========================================
		// ORDRE LEXICOGRAPHIQUE 
		// ========================================

		// On passe à l'ordre de parcours suivant selon l'ordre lexicographique
		int largestI = -1;
		for (int i = 0; i < order.size() - 1; i++) {
			if (order[i] < order[i + 1]) {
				largestI = i;
			}
		}
		if (largestI == -1) {
			// On a termine de parcourir tous les ordres possibles
			finished = true;
			break;
		}

		int largestJ = -1;
		for (int j = 0; j < order.size(); j++) {
			if (order[largestI] < order[j]) {
				largestJ = j;
			}
		}


		swap(order[largestI], order[largestJ]);

		int size = largestI + 1;
		reverse(order.begin() + size, order.end());
	}

	// Fin du chronomètre
	end = chrono::system_clock::now();


	// ================================================================================
	// AFFICHAGE DU RESULTAT 
	// ================================================================================ 

	// Affichage du meilleur ordre de parcours
	cout << "Meilleur ordre de parcours :" << endl;
	for (int &index : bestOrder) {
		cout << index << " ";
	}
	cout << endl << endl;

	// Affichage de la meilleure distance
	cout << "Distance parcourue pour cet ordre (au carre) : " << bestDist << endl;

	// Affichage de la durée d'exécution
	elapsed_seconds = end - start;
	cout << "Duree du programme : " << elapsed_seconds.count() << "s" << endl;



	return 0;
}
