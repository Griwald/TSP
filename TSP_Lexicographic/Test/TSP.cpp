// TSP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "Vect2.h"
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include <iostream>
#include <vector>	// vector
#include <utility>	// swap, reverse
#include <chrono>
#include <ctime>

using namespace std;


/* Retourne la distance totale entre les villes parcourues dans l'ordre donné */
int calcTotalDist(vector<Vect2> cities, vector<int> order)
{
	int totalDist = 0;
	for (int i = 0; i < order.size() - 1; i++) {
		Vect2 cityA = cities[order[i]];
		Vect2 cityB = cities[order[i + 1]];
		totalDist += Vect2::distSq(cityA, cityB);
	}
	return totalDist;
}


int main()
{
	int width = 500;
	int height = 500;
	int nbOfCities = 9;

	vector<Vect2> cities;
	vector<int> order;


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	srand(time(NULL));

	for (int i = 0; i < nbOfCities; i++) {
		int posX = rand() % width;
		int posY = rand() % height;
		cities.push_back(Vect2(posX, posY));

		order.push_back(i);
	}

	int bestDist = calcTotalDist(cities, order);
	vector<int> bestOrder = order;


	// ================================================================================
	// PARCOURS DU GRAPHE 
	// ================================================================================ 

	auto start = chrono::system_clock::now();

	bool finished = false;
	while (!finished) {

		// Astuce pour ne pas considérer les permutations qui donnent un ordre "inverse"
		// ex: ne pas considérer {3,2,1} qui traite le même chemin que 1,2,3}
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

	cout << "Position des villes :" << endl;
	for (Vect2 &city : cities) {
		cout << city << endl;
	}
	cout << endl;

	cout << "Meilleur ordre de parcours :" << endl;
	for (int &index : bestOrder) {
		cout << index << " ";
	}
	cout << endl << endl;

	cout << "Distance parcourue pour cet ordre (au carre) : " << bestDist << endl;


	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "Duree du programme : " << elapsed_seconds.count() << "s" << endl;


	return 0;
}
