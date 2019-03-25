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
	int windowHeight;
	int windowWidth;
	float circleSize = 5.f;

	vector<CircleShape> shapes;
	RenderWindow window;

	/* Méthodes */
	void createWindow();
	void showWindow();
	void drawCity(vector<City> cities);

	/* Constructeurs */
	SfmlWindow();
	SfmlWindow(int height, int width);

	/* Destructeurs */
	~SfmlWindow();


private:

};

