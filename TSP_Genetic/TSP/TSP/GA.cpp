#include "pch.h"
#include "GA.h"

using namespace std;


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


vector<int> select(vector<DNA>& population)
{
	// Valeur aléatoire entre 0 et 1
	double r = ((double)rand() / (RAND_MAX));

	int index = 0;
	while (r >= 0.0 && index != population.size()) {
		r -= population[index].fitness;
		index++;
	}

	// La plupart du temps c'est un ordre d'une population 
	// avec une haute valeur de fitness qui sera retournée
	return population[index-1].order;
}

vector<int> crossover(vector<int>& orderA, vector<int>& orderB)
{
	// On récupère une sous partie de l'ordre A découpée comme suit,
	// Index de début : [0, taille - 1]
	// Index de fin : [début + 1, taille]
	int nbOfCities = orderA.size();
	int start = rand() % nbOfCities;
	int min = start + 1;
	int end = rand() % (nbOfCities - min + 1) + min;
	vector<int> newOrder(orderA.begin() + start, orderA.begin() + end);

	// On ajoute les valeurs manquantes dans l'ordre d'apparition de ces valeurs dans l'ordre B
	for (int i = 0; i < orderB.size(); i++) {
		int cityIndex = orderB[i];
		// Si on ne trouve pas la ville ...
		if (find(newOrder.begin(), newOrder.end(), cityIndex) == newOrder.end()) {
			// ... on l'ajoute
			newOrder.push_back(cityIndex);
		}
	}

	return newOrder;
}

void mutate(vector<int>& order, double mutationRate)
{
	// On tente autant de mutation que le nombre de villes
	int nbOfCities = order.size();
	for (int i = 0; i < nbOfCities; i++) {
		// Valeur aléatoire entre 0 et 1
		double r = ((double)rand() / (RAND_MAX));

		// S'il y a mutation ...
		if (r < mutationRate) {
			// ... on échange deux valeurs successives
			int indexA = rand() % nbOfCities;
			int indexB = (indexA + 1) % nbOfCities;
			swap(order[indexA], order[indexB]);
		}
	}
}


void calculateFitness(vector<DNA>& population)
{
	// Pour chaque population, ...
	for (int i = 0; i < population.size(); i++) {
		// ... on récupère son ordre de parcours ...
		vector<int> currentOrder = population[i].order;
		// ... on calcule sa distance totale de parcours théorique (fonction objectif) ...
		unsigned int dist = calcTotalDist(cities, currentOrder);
		// ... puis on affecte à la popuplation une valeur de fitness sera inversement 
		// proportionnelle à la distance, et la mise à la puissance élévée permet 
		// d'affecter une valeur de fitness très faible aux distances de parcours élévée
		// qui auront moins de chances d'être séléctionnées dans la méthode select()
		population[i].fitness = 1.0 / (pow(dist, 8) + 1);
	}
}

void normalizeFitness(vector<DNA>& population)
{
	// Calcul de la somme totale des valeurs de fitness
	double sum = 0.0;
	for (int i = 0; i < population.size(); i++) {
		sum += population[i].fitness;
	}

	for (int i = 0; i < population.size(); i++) {
		// Chaque valeur de fitness est entre 0 et 1 et leur somme s'ajoute jusqu'à 1
		population[i].fitness /= sum;
	}
}

void nextGeneration(vector<DNA>& population)
{
	// Création d'une nouvelle popultation à partir de la précédente
	vector<DNA> newPopulation(population.size());

	// Pour chaque population, ...
	for (int i = 0; i < population.size(); i++) {
		// ... on récupère deux ordres, ...
		vector<int> orderA = select(population);
		vector<int> orderB = select(population);
		// ... on les combine en un nouveau, ...
		vector<int> order = crossover(orderA, orderB);
		// ... puis on tente de le muter
		mutate(order, 0.01);
		newPopulation[i] = DNA(order);
	}

	population = newPopulation;
}
