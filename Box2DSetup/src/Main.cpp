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
	
	RectangleWorldObject ground(world, b2_staticBody, sf::Color::White, screenWidth / 4.f, screenHeight / 2.f, screenWidth / 2.f, 50.f);

	//Robot generation
	CircleWorldObject wheelRight(world, b2_dynamicBody, sf::Color::White, 1100.f, -500.f, 120.f);
	CircleWorldObject wheelLeft(world, b2_dynamicBody, sf::Color::White, 200.f, 200.f, 150.f);
	RectangleWorldObject armLeft(world, b2_dynamicBody, sf::Color::Blue, 400.f, -200.f, 500.f, 30.f);
	RectangleWorldObject armRight(world, b2_dynamicBody, sf::Color::Red, 700.f, -100.f, 500.f, 30.f);
	ConvexWorldObject triangle(world, b2_dynamicBody, ConvexWorldObject::ConvexShape::EquilateralTriangle, sf::Color::Blue, 500.f, 100.f, 200.f, 100.f);

	/*
	//Joint Center
	b2RevoluteJointDef jointCenterDef;
	jointCenterDef.bodyA = armLeft.getPhysicalBody();
	jointCenterDef.bodyB = armRight.getPhysicalBody();
	jointCenterDef.collideConnected = false;
	jointCenterDef.localAnchorA.Set(-250.f / SCALE, 0.f / SCALE);
	jointCenterDef.localAnchorB.Set(-250.f / SCALE, 0.f / SCALE);
	jointCenterDef.referenceAngle = -b2_pi / 2.f;
	b2RevoluteJoint* jointCenter = (b2RevoluteJoint*)world.CreateJoint(&jointCenterDef);


	//Joint Left
	b2RevoluteJointDef jointLeftDef;
	jointLeftDef.bodyA = wheelLeft.getPhysicalBody();
	jointLeftDef.bodyB = armLeft.getPhysicalBody();
	jointLeftDef.collideConnected = false;
	jointLeftDef.localAnchorA.Set(0.f / SCALE, 0.f / SCALE);
	jointLeftDef.localAnchorB.Set(250.f / SCALE, 0.f / SCALE);
	jointLeftDef.referenceAngle = 0.f;
	b2RevoluteJoint* jointLeft = (b2RevoluteJoint*)world.CreateJoint(&jointLeftDef);

	//Joint Right
	b2RevoluteJointDef jointRightDef;
	jointRightDef.bodyA = wheelRight.getPhysicalBody();
	jointRightDef.bodyB = armRight.getPhysicalBody();
	jointRightDef.collideConnected = false;
	jointRightDef.localAnchorA.Set(0.f / SCALE, 0.f / SCALE);
	jointRightDef.localAnchorB.Set(250.f / SCALE, 0.f / SCALE);
	jointRightDef.referenceAngle = 0.f;
	b2RevoluteJoint* jointRight = (b2RevoluteJoint*)world.CreateJoint(&jointRightDef);
	*/


	//Simulation
	float timeStep = 1.f / 30.f;
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
