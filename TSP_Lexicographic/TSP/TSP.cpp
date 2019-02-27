// TSP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "City.h"
#include <iostream>
#include <vector>	// vector
#include <climits>  // UINT_MAX
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include <utility>	// swap, reverse
#include <chrono>

using namespace std;


/* Retourne la distance totale entre les villes parcourues dans l'ordre donné */
int calcTotalDist(vector<City> cities, vector<int> order)
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
	int width = 500;	// Largeur de l'espace de placement des villes
	int height = 500;	// Hauteur de l'espace de placement des villes
	int nbOfCities = 5; // Nombre de villes placees dans l'espace

	vector<City> cities; // Structure qui contient les villes
	vector<int> order;	 // Structure qui contient l'ordre de parcours des villes


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de generation aleatoire
	srand(time(NULL));

	// Création des villes
	for (int i = 0; i < nbOfCities; i++) {
		int posX = rand() % width;
		int posY = rand() % height;
		cities.push_back(City(i, posX, posY));

		// Remplissage de la stucture d'ordre de parcours
		order.push_back(i);
	}

	// Affichage de la position des villes
	cout << "Position des villes :" << endl;
	for (City &city : cities) {
		cout << city << endl;
	}
	cout << endl;

	// Initialisation de la meilleure distance de parcours et du meilleur ordre
	unsigned int bestDist = UINT_MAX;
	vector<int> bestOrder = order;


	// ================================================================================
	// PARCOURS DU GRAPHE 
	// ================================================================================ 

	// Début du chronometre
	auto start = chrono::system_clock::now();

	bool finished = false;
	while (!finished) {

		// Astuce pour ne pas considérer les permutations qui donnent un ordre "inverse"
		// ex: ne pas considérer {3,2,1} qui traite le même chemin que {1,2,3}
		if (order[0] < order[order.size() - 1]) {
			// On calcule la distance de parcours total avec l'ordre actuel
			int dist = calcTotalDist(cities, order);
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
			// On a terminé de parcourir tous les ordres possibles
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
