//#include <SFML/Graphics.hpp>
//
//
//using namespace std;
//using namespace sf;
//
//int main()
//{
//	int windowHeight = 960;
//	int windowWidth = 540;
//	float circleSize = 100.f;
//
//	RenderWindow window(VideoMode(windowHeight, windowWidth), "SFML works!");
//	CircleShape shape(circleSize);
//	shape.setFillColor(Color::Green);
//	shape.setPosition(windowHeight/2 - circleSize, windowWidth/2 - circleSize);
//	//shape.setPosition(windowHeight / 2, windowWidth/2);
//
//
//	while (window.isOpen())
//	{
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}