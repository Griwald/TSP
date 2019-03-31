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


vector<int> selection(vector<DNA>& population)
{
	// Valeur al�atoire entre 0 et 1
	double r = ((double)rand() / (RAND_MAX));

	// On cherche le dernier individu qui, gr�ce � sa valeur de fitness accumul�e,
	// rendra la valeur al�atoire n�gative ou nulle
	int index = 0;
	while (r >= 0.0 && index != population.size()) {
		r -= population[index].fitness;
		index++;
		if (index == population.size()) {
			break;
		}
	}

	// La plupart du temps c'est un ordre d'une population 
	// avec une haute valeur de fitness qui sera retourn�e
	return population[index-1].order;
}

vector<int> crossover(vector<int>& orderA, vector<int>& orderB)
{
	// On r�cup�re une sous partie de l'ordre A d�coup�e comme suit,
	// Index de d�but : [0, taille - 1]
	// Index de fin : [d�but + 1, taille]
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

void mutation(vector<int>& order, double mutationRate)
{
	// On tente autant de mutation que le nombre de villes
	int nbOfCities = order.size();
	for (int i = 0; i < nbOfCities; i++) {
		// Valeur al�atoire entre 0 et 1
		double r = ((double)rand() / (RAND_MAX));

		// S'il y a mutation ...
		if (r < mutationRate) {
			// ... on �change deux valeurs successives
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
		// ... on r�cup�re son ordre de parcours ...
		vector<int> currentOrder = population[i].order;
		// ... on calcule sa distance totale de parcours th�orique (fonction objectif) ...
		unsigned int dist = calcTotalDist(cities, currentOrder);
		// ... puis on affecte � la popuplation une valeur de fitness sera inversement 
		// proportionnelle � la distance, et la mise � la puissance �l�v�e permet 
		// d'affecter une valeur de fitness tr�s faible aux distances de parcours �l�v�e
		// qui auront moins de chances d'�tre s�l�ctionn�es dans la m�thode selection()
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
		// Chaque valeur de fitness est entre 0 et 1 et leur somme s'ajoute jusqu'� 1
		population[i].fitness /= sum;
	}
}

void nextGeneration(vector<DNA>& population)
{
	// Cr�ation d'une nouvelle popultation � partir de la pr�c�dente
	vector<DNA> newPopulation(population.size());

	// Pour chaque population, ...
	for (int i = 0; i < population.size(); i++) {
		// ... on r�cup�re deux ordres, ...
		vector<int> orderA = selection(population);
		vector<int> orderB = selection(population);
		// ... on les combine en un nouveau, ...
		vector<int> order = crossover(orderA, orderB);
		// ... puis on tente de le muter
		mutation(order, 0.01);
		newPopulation[i] = DNA(order);
	}

	population = newPopulation;
}
