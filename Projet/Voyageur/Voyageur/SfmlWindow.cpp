#include "SfmlWindow.h"

//#include <SFML/Graphics.hpp> // sf::librairie graphique SFML

using namespace sf;

void SfmlWindow::createWindow()
{
	this->window.create(VideoMode(this->windowWidth, this->windowHeight), "Voyageur de commerce");
}

void SfmlWindow::showWindow()
{
	while (window.isOpen())
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				this->window.close();
		}

		//this->window.clear();

		// draw les cercles pour les villes
		for (int i = 0; i < this->shapes.size(); i++) {
			this->window.draw(shapes[i]);
		}

		// draw les lignes
		for (int i = 0; i < this->shapes.size()-1; i++) {

			//this->shapes[(this->order[i])].getPosition().x;
			float posP1x = this->shapes[(this->order[i])].getPosition().x;
			float posP1y = this->shapes[(this->order[i])].getPosition().y;
			float posP2x = this->shapes[(this->order[i+1])].getPosition().x;
			float posP2y = this->shapes[(this->order[i+1])].getPosition().y;

			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(posP1x, posP1y)),
				sf::Vertex(sf::Vector2f(posP2x , posP2y))
			};
			
			if (i == 0) {
				line->color = Color::Red;
			}
			else {
				line->color = Color::White;
			}

			window.draw(line, 2, sf::Lines);
		}

		
		//this->window.draw(shape);

		this->window.display();
	}
}

void SfmlWindow::drawCity(vector<City> &cities, vector<int> order)
{
	float maxCityWidth = 200.f;
	float maxCityHeight = 200.0f;

	this->order = order;

	//CircleShape shapes 
	this->window.clear();

	for (int i = 0; i < cities.size(); i++) {

		cout << cities[i] << endl;

		CircleShape newShape(this->circleSize);
		newShape.setFillColor(Color::White);

		float newX = ((cities[i].posX * this->canvasWidth) / maxCityWidth) + 10 ;
		float newY = ((cities[i].posY * this->canvasHeight) / maxCityHeight) + 10;
		newShape.setPosition(newX, newY);

		this->shapes.push_back(newShape);
	}
}

SfmlWindow::SfmlWindow()
{
	this->windowWidth = 960;
	this->windowHeight = 540;

	this->canvasHeight = this->windowHeight - 20;
	this->canvasWidth = this->windowWidth - 20;
}

SfmlWindow::SfmlWindow(int height, int width)
{
	this->windowHeight = height;
	this->windowWidth = width;

	this->canvasHeight = this->windowHeight - 20;
	this->canvasWidth = this->windowWidth - 20;
}


SfmlWindow::~SfmlWindow()
{
}
