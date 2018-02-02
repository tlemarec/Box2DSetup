#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#include <stdio.h>
#include <iostream>


int main(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	const double SCALE = 30.0;
	//window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	window.setFramerateLimit(60);
	
	// SFML Shapes
	//falling object
	sf::RectangleShape dynamicShape;
	dynamicShape.setSize(sf::Vector2f(100, 100));
	dynamicShape.setFillColor(sf::Color::Blue);

	//ground
	sf::RectangleShape groundShape;
	groundShape.setSize(sf::Vector2f(1920, 100));
	groundShape.setFillColor(sf::Color::Green);


	//World
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);

	// Dynamic Body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(100 / SCALE, 100 / SCALE);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((100.f / 2) / SCALE, (100.f / 2) / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);


	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position = b2Vec2(0 / SCALE, 900 / SCALE);
	groundBodyDef.type = b2_staticBody;
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	
	b2PolygonShape groundBox;
	groundBox.SetAsBox((800.f / 2) / SCALE, (100.f / 2) / SCALE);
	groundBody->CreateFixture(&groundBox, 0.0f);


	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	
	while (window.isOpen())
	{
		
		for (int32 i = 0; i < 60; ++i)
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
			
			for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
			{
				if (BodyIterator->GetType() == b2_dynamicBody)
				{

					dynamicShape.setOrigin(50, 50);
					dynamicShape.setPosition(BodyIterator->GetPosition().x * 30, BodyIterator->GetPosition().y * 30);
					dynamicShape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					window.draw(dynamicShape);

				}

				else if (BodyIterator->GetType() == b2_staticBody)
				{
					groundShape.setOrigin(800, 0);
					groundShape.setPosition(BodyIterator->GetPosition().x * 30, BodyIterator->GetPosition().y * 30);
					groundShape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);

					window.draw(groundShape);

				}
			}

			window.display();


			// Console output
			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

		}


	}

	std::cin.get();
	
	return 0;
}
