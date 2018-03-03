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
	sf::RenderWindow window(sf::VideoMode(screenWidth / 2.f, screenHeight / 2.f), "SFML works!");
	window.setFramerateLimit(60);
	
	//Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);
	WorldObject ground(world, WorldObject::Rectangle, WorldObject::ObjectType::Static, sf::Color::White, screenWidth / 4.f, screenHeight / 2.f, screenWidth / 2.f, 50.f);

	//Robot generation
	CircleWorldObject wheelLeft(world, CircleWorldObject::ObjectType::Static, sf::Color::White, 200.f, 400.f, 300.f, 30.f);
	CircleWorldObject wheelRight(world, CircleWorldObject::ObjectType::Dynamic , sf::Color::Red, 200.f , -100.f, 30.f, 30.f);

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

			ground.positionUpdate();
			ground.imageRender(window);

			wheelLeft.positionUpdate();
			wheelLeft.imageRender(window);

			wheelRight.positionUpdate();
			wheelRight.imageRender(window);

			window.display();

			// Console output
			wheelLeft.GetPosition("wheelLeft");
			wheelRight.GetPosition("wheelRight");
			ground.GetPosition("ground");
			
		}


	}

	std::cin.get();
	return EXIT_SUCCESS;
}
