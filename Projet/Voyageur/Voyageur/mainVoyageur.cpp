// TSP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "City.h"
#include "SfmlWindow.h"
#include "GA.h"
#include "DNA.h"

using namespace std;


/* Fonction objectif :
 * Retourne la distance totale entre les villes parcourues dans l'ordre donné
 */
int calcTotalDistLexico(vector<City>& cities, vector<int>& order)
{
	int totalDist = 0;
	for (int i = 0; i < order.size() - 1; i++) {
		City cityA = cities[order[i]];
		City cityB = cities[order[i + 1]];
		totalDist += City::distSq(cityA, cityB);
	}
	return totalDist;
}



/* Fonction objectif : 
 * paramétrage des coordonnées des villes aléatoirement
 */
void settingCitiesRandom(vector<City> &cities, vector<int> &order, int &nbOfCities) {

	int width = 200;	// Largeur de l'espace de placement des villes
	int height = 200;	// Hauteur de l'espace de placement des villes
	
	// Création des villes
	for (int i = 0; i < nbOfCities; i++) {
		int posX = rand() % width;
		int posY = rand() % height;
		cities[i] = City(i, posX, posY);

		// Remplissage de la stucture d'ordre de parcours
		order[i] = i;
	}
}



/* Fonction objectif :
 * paramétrage des coordonnées des villes aléatoirement
 */
void settingCitiesManual(vector<City> &cities, vector<int> &order, int &nbOfCities) {

	int width = 200;	// Largeur de l'espace de placement des villes
	int height = 200;	// Hauteur de l'espace de placement des villes

	// Création des villes
	for (int i = 0; i < nbOfCities; i++) {
		cout << "Coordonnees de la ville (maximum 200)" << i << " : ( x puis y ) " << endl;
		int tempX, tempY;
		cin >> tempX;
		cin >> tempY;
		cities[i] = City(i, tempX, tempY);

		// Remplissage de la stucture d'ordre de parcours
		order[i] = i;
	}
}



/* Fonction objectif :
 * donne l'ordre de la ville à l'aide de la solution lexicographique
 */
void lexicographicMethod(vector <City> &cities, vector<int> &order) {

	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de géneration aléatoire
	srand(time(NULL));


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

	// Début du chronomètre
	auto start = chrono::system_clock::now();

	bool finished = false;
	while (!finished) {

		// Astuce pour ne pas considérer les permutations qui donnent un ordre "inverse"
		// ex: ne pas considérer {3,2,1} qui traite le même chemin que {1,2,3}
		if (order[0] < order[order.size() - 1]) {
			// On calcule la distance de parcours total avec l'ordre actuel
			int dist = calcTotalDistLexico(cities, order);
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

	SfmlWindow mainWindow;

	mainWindow.createWindow();
	mainWindow.drawCity(cities, bestOrder);
	mainWindow.showWindow();

}


/* Fonction objectif :
 * donne l'ordre de la ville à l'aide de la solution genetique
 */
void geneticMethod(vector <City> &cities, vector<int> &order) {

	const int nbOfPopulation = 200;	 // Taille de la population
	const int nbOfGenerations = 50;	 // Nombre de générations

	vector<DNA> population; // Structure qui contient la population


	// ================================================================================
	// INITIALISATION 
	// ================================================================================ 

	// Initialisation du germe de génération aléatoire
	srand(time(NULL));

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
		calculateFitness(population, cities);
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

	SfmlWindow mainWindow;

	mainWindow.createWindow();
	mainWindow.drawCity(cities, bestOrder);
	mainWindow.showWindow();

}




int main()
{
	int choix;
	int width = 200;	// Largeur de l'espace de placement des villes
	int height = 200;	// Hauteur de l'espace de placement des villes
	int nbOfCities/* = 10*/; // Nombre de villes placées dans l'espace
	



	cout << "Resolution du voyageur de commerce. \nAlgorithmique - 8INF870 \nTravail par Dylan DEMANGE et Nicolas MARIN \nUtilisation d'une methode exacte et d'une methode approchée" << endl << endl;
	
	cout << "Veuillez choisir le nombre de villes : " << endl;
	cin >> choix;
	nbOfCities = choix;

	vector<City> cities(nbOfCities); // Structure qui contient les villes
	vector<int> order(nbOfCities);	 // Structure qui contient l'ordre de parcours des villes

	cout << "Nombre de villes : " << choix << endl << endl;
	cout << "Ville place aleatoirement (choix 1) ou predefini (choix 2) : " << endl;
	
	cout << "Entrez votre choix : " << endl; 
	cin >> choix;

	switch (choix)
	{
	case 1:
		settingCitiesRandom(cities, order,nbOfCities);
		break;
	case 2:
		settingCitiesManual(cities, order, nbOfCities);
		break;
	default:
		cout << "Choix invalide, sélection aléatoire" << endl;
		settingCitiesRandom(cities, order, nbOfCities);
		break;
	}


	cout << "Menu de choix des méthodes : " << endl;
	cout << "   1 - Methode exacte" << endl;
	cout << "   2 - Methode approchee : Algorithme genetique" << endl;
	cout << "   3 - Utilisation des deux methodes" << endl;
	cout << "   4 - Quitter le programme" << endl << endl;

	cout << "Entrez votre choix : " << endl;
	
	cin >> choix;
	cout << "Choix : " << choix << endl << endl;



	switch (choix)
	{
		case 1:
			cout << "Methode exacte" << endl;
			lexicographicMethod(cities, order);
			break;
		case 2:
			cout << "Methode approchee : Algorithme genetique" << endl;
			geneticMethod(cities, order);
			break;
		case 3:
			cout << "Utilisation des deux methodes" << endl;	
			lexicographicMethod(cities, order);
			geneticMethod(cities, order);
			break;
		case 4:
			break;
		default:
			cout << "Choix Invalide !" << endl;
			break;
	}
	cout << "Votre choix : " << choix << endl;;
	   	 	

	cout << "Fin de programme " << endl;

	while (true);
	return 0;
}
