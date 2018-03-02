#include <windows.h>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#include <stdio.h>
#include <iostream>

#include "WorldObject.h"

#define SCALE 30.f


int main(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//System info
	::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	std::cout << "width : " << screenWidth << ", height : " << screenHeight << std::endl;
	
	//SFML Window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
	window.setFramerateLimit(60);
	
	//Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);
	WorldObject ground(world, WorldObject::Rectangle, b2_staticBody, sf::Color::White, screenWidth/2.f, screenHeight, screenWidth, 300.f);

	//Robot generation

	
	//Simulation
	float timeStep = 1.f / 60.f;
	int velocityIterations = 6;
	int positionIterations = 2;
	while (window.isOpen())
	{
		
		for (int i = 0; i < 60; ++i)
		{
			// Step Simulation
			world.Step(timeStep, velocityIterations, positionIterations);
			window.clear();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			ground.update();
			ground.render(window);

			window.display();

			// Console output
			ground.GetPosition();
			
		}


	}

	std::cin.get();
	return 0;
}
