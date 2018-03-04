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
	sf::RenderWindow window(sf::VideoMode(screenWidth / 2, screenHeight / 2), "SFML works!");
	window.setFramerateLimit(60);
	
	//Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);
	
	RectangleWorldObject ground(world, RectangleWorldObject::ObjectType::Static, sf::Color::White, screenWidth / 4.f, screenHeight / 2.f, screenWidth / 2.f, 50.f);

	//Robot generation
	CircleWorldObject wheelRight(world, CircleWorldObject::ObjectType::Dynamic, sf::Color::White, 1100.f, -500.f, 120.f, 120.f);
	CircleWorldObject wheelLeft(world, CircleWorldObject::ObjectType::Static, sf::Color::White, 500.f, 500.f);
	RectangleWorldObject armLeft(world, RectangleWorldObject::ObjectType::Dynamic, sf::Color::White, 600.f, -300.f, 30.f, 200.f);
	RectangleWorldObject armRight(world, RectangleWorldObject::ObjectType::Dynamic, sf::Color::Red, 500.f, -100.f, 2000.f, 30.f);
	ConvexWorldObject triangle(world, ConvexWorldObject::EquilateralTriangle, ConvexWorldObject::ObjectType::Dynamic, sf::Color::Blue, 500.f, 100.f, 200.f, 100.f);


	////Joint Left
	//b2RevoluteJointDef jointLeftDef;
	//jointLeftDef.bodyA = wheelLeft.getPhysicalBody();
	//jointLeftDef.bodyB = armLeft.getPhysicalBody();
	//jointLeftDef.collideConnected = false;
	//jointLeftDef.localAnchorA.Set(0.f, 0.f);
	//jointLeftDef.localAnchorB.Set(70.f, 0);
	//jointLeftDef.referenceAngle = 0.f;
	//b2RevoluteJoint* jointLeft = (b2RevoluteJoint*)world.CreateJoint(&jointLeftDef);

	//Simulation
	float timeStep = 1.f / 90.f;
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

			triangle.positionUpdate();
			triangle.imageRender(window);

			wheelLeft.positionUpdate();
			wheelLeft.imageRender(window);

			wheelRight.positionUpdate();
			wheelRight.imageRender(window);

			armLeft.positionUpdate();
			armLeft.imageRender(window);

			armRight.positionUpdate();
			armRight.imageRender(window);

			window.display();

			//Console output
			//wheelLeft.getPosition("wheelLeft");
			//armLeft.getPosition("armLeft");
			//wheelRight.getPosition("wheelRight");
			//armRight.getPosition("armRight");
			//ground.getPosition("ground");

		}
	}

	std::cin.get();
	return EXIT_SUCCESS;
}
