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


vector<int> pickBest(vector<DNA>& population)
{
	// Valeur aléatoire entre 0 et 1
	double r = ((double)rand() / (RAND_MAX));

	int index = 0;
	while (r >= 0.0) {
		r -= population[index].fitness;
		index++;
		if (index == population.size()) {
			break;
		}
	}
	return population[index-1].order;
}

vector<int> crossover(vector<int>& orderA, vector<int>& orderB)
{
	int nbOfCities = orderA.size();
	int start = rand() % nbOfCities;
	int min = start + 1;
	int end = rand() % (nbOfCities - min + 1) + min;

	vector<int> newOrder(orderA.begin() + start, orderA.begin() + end);

	for (int i = 0; i < orderB.size(); i++) {
		int cityIndex = orderB[i];
		if (find(newOrder.begin(), newOrder.end(), cityIndex) == newOrder.end()) {
			newOrder.push_back(cityIndex);
		}
	}

	return newOrder;
}

void mutate(vector<int>& order, double mutationRate)
{
	int nbOfCities = order.size();
	for (int i = 0; i < nbOfCities; i++) {
		double r = ((double)rand() / (RAND_MAX));
		if (r < mutationRate) {
			int indexA = rand() % nbOfCities;
			int indexB = (indexA + 1) % nbOfCities;
			swap(order[indexA], order[indexB]);
		}
	}
}


void calcFitness(vector<DNA>& population)
{
	for (int i = 0; i < population.size(); i++) {
		vector<int> currentOrder = population[i].order;
		unsigned int dist = calcTotalDist(cities, currentOrder);
		population[i].fitness = 1.0 / (pow(dist, 8) + 1);
	}
}

void normalizeFitness(vector<DNA>& population)
{
	double sum = 0.0;
	for (int i = 0; i < population.size(); i++) {
		sum += population[i].fitness;
	}
	for (int i = 0; i < population.size(); i++) {
		population[i].fitness /= sum;
	}
}

void nextGeneration(vector<DNA>& population)
{
	vector<DNA> newPopulation(population.size());
	for (int i = 0; i < population.size(); i++) {
		vector<int> orderA = pickBest(population);
		vector<int> orderB = pickBest(population);
		vector<int> order = crossover(orderA, orderB);
		mutate(order, 0.01);
		newPopulation[i] = DNA(order);
	}
	population = newPopulation;
}
