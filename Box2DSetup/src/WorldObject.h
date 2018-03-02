#ifndef pgcdHPP
#define pgcdHPP

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.f

class WorldObject
{
private:
	b2Body * physicalBody;
	sf::ConvexShape renderShape;
public:
	static enum ObjectShape { EquilateralTriangle, Square, Rectangle, Circle};
	WorldObject(b2World& world, const WorldObject::ObjectShape shape = WorldObject::Square, const b2BodyType type = b2_dynamicBody ,const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;
		

		switch (type)
		{
		case b2_dynamicBody:
			{
				bodyDef.type = b2_dynamicBody;
				fixture.density = 1.0f;
			}
		case b2_staticBody:
		{
			bodyDef.type = b2_staticBody;
			fixture.density = 0.0f;
		}
		}

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = 0;
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.3f;
		fixture.restitution = 0.5f;

		b2PolygonShape bodyShape;
		switch (shape)
		{
		case EquilateralTriangle:
			{
				float sizeInPixels = widthInPixels;
				float sizeInMKS = sizeInPixels / SCALE;

				const int pointCount = 3;
				b2Vec2 points[pointCount] = { b2Vec2(sizeInMKS,0), b2Vec2(-sizeInMKS,sizeInMKS), b2Vec2(-sizeInMKS,-sizeInMKS) };
				bodyShape.Set(points, pointCount);

				fixture.shape = &bodyShape;
				physicalBody->CreateFixture(&fixture);

				renderShape.setPointCount(3);
				renderShape.setPoint(0, sf::Vector2f((points[0].x * SCALE), (points[0].y * SCALE)));
				renderShape.setPoint(1, sf::Vector2f((points[1].x * SCALE), (points[1].y * SCALE)));
				renderShape.setPoint(2, sf::Vector2f((points[2].x * SCALE), (points[2].y * SCALE)));
				break;
			}
		case Square:
		default:
			{
				float sizeInPixels = widthInPixels;
				float sizeInMKS = sizeInPixels / SCALE;

				bodyShape.SetAsBox((sizeInPixels / 2.f) / SCALE, (sizeInPixels / 2.f) / SCALE);

				fixture.shape = &bodyShape;
				physicalBody->CreateFixture(&fixture);

				renderShape.setPointCount(4);
				renderShape.setPoint(0, sf::Vector2f(0.f, 0.f));
				renderShape.setPoint(1, sf::Vector2f(sizeInPixels, 0.f));
				renderShape.setPoint(2, sf::Vector2f(sizeInPixels, sizeInPixels));
				renderShape.setPoint(3, sf::Vector2f(0.f, sizeInPixels));
				renderShape.setOrigin(sizeInPixels / 2.f, sizeInPixels / 2.f);
				break;
			}
		case Rectangle:
			{
				float widthInMKS = widthInPixels / SCALE;
				float heightInMKS = heightInPixels / SCALE;

				bodyShape.SetAsBox((widthInPixels / 2.f) / SCALE, (heightInPixels / 2.f) / SCALE);

				fixture.shape = &bodyShape;
				physicalBody->CreateFixture(&fixture);

				renderShape.setPointCount(4);
				renderShape.setPoint(0, sf::Vector2f(0.f, 0.f));
				renderShape.setPoint(1, sf::Vector2f(widthInPixels, 0.f));
				renderShape.setPoint(2, sf::Vector2f(widthInPixels, heightInPixels));
				renderShape.setPoint(3, sf::Vector2f(0.f, heightInPixels));
				renderShape.setOrigin(widthInPixels / 2.f, heightInPixels / 2.f);
				break;
			}
		case Circle:
			{	
				float widthInMKS = widthInPixels / SCALE;
				float heightInMKS = heightInPixels / SCALE;

				bodyShape.SetAsBox((widthInPixels / 2.f) / SCALE, (heightInPixels / 2.f) / SCALE);

				fixture.shape = &bodyShape;
				physicalBody->CreateFixture(&fixture);

				renderShape.setPointCount(4);
				renderShape.setPoint(0, sf::Vector2f(0.f, 0.f));
				renderShape.setPoint(1, sf::Vector2f(widthInPixels, 0.f));
				renderShape.setPoint(2, sf::Vector2f(widthInPixels, heightInPixels));
				renderShape.setPoint(3, sf::Vector2f(0.f, heightInPixels));
				renderShape.setOrigin(widthInPixels / 2.f, heightInPixels / 2.f);
				break;
			}
		}
		renderShape.setFillColor(color);
		renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
		renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));
	}
	
	void update();

	void render(sf::RenderWindow& renderWindow);
	
	void GetPosition();
};

#endif