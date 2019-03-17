// TSP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "City.h"
#include <iostream> // std::cout 
#include <vector>	// std::vector
#include <utility>	// std::swap, std::reverse
#include <cstdlib>  // std::rand, std::srand
#include <ctime>    // std::time
#include <chrono>	// std::chrono::
#include <climits>  // UINT_MAX

using namespace std;


/* Retourne la distance totale entre les villes parcourues dans l'ordre donné */
int calcTotalDist(vector<City>& cities, vector<int>& order)
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
	int width = 200;	// Largeur de l'espace de placement des villes
	int height = 200;	// Hauteur de l'espace de placement des villes
	int nbOfCities = 7; // Nombre de villes placees dans l'espace

	vector<City> cities(nbOfCities); // Structure qui contient les villes
	vector<int> order(nbOfCities);	 // Structure qui contient l'ordre de parcours des villes


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de generation aleatoire
	srand(time(NULL));

	// Création des villes
	for (int i = 0; i < nbOfCities; i++) {
		int posX = rand() % width;
		int posY = rand() % height;
		cities[i] = City(i, posX, posY);

		// Remplissage de la stucture d'ordre de parcours
		order[i] = i;
	}

	// Initialisation de la meilleure distance de parcours et du meilleur ordre
	unsigned int bestDist = UINT_MAX;
	vector<int> bestOrder = order;

	// Affichage de la position des villes
	cout << "Position des villes :" << endl;
	for (City &city : cities) {
		cout << city << endl;
	}
	cout << endl;


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
