#pragma once

#include "pch.h"
#include "City.h"

using namespace std;
using namespace sf;

/*
Classe gérant les fonctionnalités de la fenêtre graphique via SFML
*/

class SfmlWindow
{
public:

	/* Attributs */
	int windowHeight; // hauteur de la fenetre
	int windowWidth; // largeur de la fenetre
	int canvasHeight; // hauteur zone dessin
	int canvasWidth; // largeur zone dessin

	float circleSize = 5.f; // dimension cercle ville

	vector<CircleShape> shapes; // cercle ville
	vector<Text> textNbCity; // pos de la ville

	vector<int> order; // ordre de passage du voyageur

	RenderWindow window; // fenetre d'affichage

	/* Méthodes */
	void createWindow();
	void showWindow();
	void drawCity(vector<City> &cities, vector<int> order);

	/* Constructeurs */
	SfmlWindow();
	SfmlWindow(int height, int width);

	/* Destructeurs */
	~SfmlWindow();


private:

};

