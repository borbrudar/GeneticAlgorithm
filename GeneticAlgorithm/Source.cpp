#include <SFML/Graphics.hpp>
#include "Population.h"
#include <iostream>

using namespace sf;
int main() {
	int width = 640;
	int height = 480;
	Population test(400);
	//Setup
	RenderWindow window;
	window.create(VideoMode(width, height), "Genetic Algorithm");
	Event event;

	//Goal
	CircleShape goal(5.0f);
	goal.setFillColor(Color::Green);
	goal.setOutlineThickness(1.0f);
	goal.setOutlineColor(Color::Black);
	goal.setPosition( width / 2.0f, 10.0f);

	//Obstacles
	RectangleShape obs;
	obs.setSize(Vector2f(550.0f, 15.0f));
	obs.setPosition(Vector2f(0.0f, 300.0f));
	obs.setFillColor(Color::Blue);


	//Game loop
	while (window.isOpen())
	{
		//Close window
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (test.areDotsDead())
		{
			//Genetic algorithm
			test.calculateFitness(goal.getPosition().x,goal.getPosition().y);
			test.naturalSelection();
			test.mutateDemBabies();

			
			
		}
		else
		{
			test.update(goal.getPosition().x,goal.getPosition().y);
			//Drawing
			window.clear(sf::Color(200, 200, 200, 255));
			//----------------------------------------------
			window.draw(goal);
			test.draw(window);

			window.draw(obs);
			//----------------------------------------------
			window.display();
		}
	}
	return 0;
}
