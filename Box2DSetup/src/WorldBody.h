#ifndef pgcdHPP
#define pgcdHPP

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.0

class WorldBody {

public:

	b2Body* boxBody;
	sf::RectangleShape sfmlShape;

	void generateWorldBody(b2World world, b2Vec2 position, b2BodyType type, float width, float height, sf::Color color) {
		b2BodyDef boxBodyDef;
		boxBodyDef.position = position;
		boxBodyDef.type = type;
		boxBody = world.CreateBody(&boxBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
		boxBody->CreateFixture(&boxShape, 0.0f);

		sfmlShape.setSize(sf::Vector2f(width, height));
		sfmlShape.setFillColor(color);
	}
};

#endif