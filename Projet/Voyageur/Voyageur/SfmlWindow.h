#pragma once

#include "pch.h"
#include "City.h"

using namespace std;
using namespace sf;

/*
Classe g�rant les fonctionnalit�s de la fen�tre graphique via SFML
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

	/* M�thodes */
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

