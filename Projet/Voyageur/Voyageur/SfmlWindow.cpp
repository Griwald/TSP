#include "SfmlWindow.h"

//#include <SFML/Graphics.hpp> // sf::librairie graphique SFML

using namespace sf;

void SfmlWindow::createWindow()
{
	this->window.create(VideoMode(this->windowHeight, this->windowWidth), "Voyageur de commerce");
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
		/*for (int i = 0; i < this->shapes.size(); i++) {
			this->window.draw(shapes[i]);
		}*/
		//this->window.draw(shape);
		this->window.display();
	}
}

void SfmlWindow::drawCity(vector<City> cities)
{
	float circleSize = 1.f;
	//CircleShape shapes 
	this->window.clear();
	for (int i = 0; i < cities.size(); i++) {
		cout << cities[i] << endl;
		CircleShape newShape(circleSize);
		newShape.setFillColor(Color::White);
		newShape.setPosition(i * 5, i * 5);
		this->shapes[i] = newShape;
		
	}
}

SfmlWindow::SfmlWindow()
{
	this->windowHeight = 960;
	this->windowWidth = 540;
}

SfmlWindow::SfmlWindow(int height, int width)
{
	this->windowHeight = height;
	this->windowWidth = width;
}


SfmlWindow::~SfmlWindow()
{
}
