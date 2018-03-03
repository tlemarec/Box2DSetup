#ifndef pgcdHPP
#define pgcdHPP

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.f

class WorldObject
{
private:
	b2Body* physicalBody;
	sf::ConvexShape renderShape;

public:
	static enum ObjectShape { EquilateralTriangle, Square, Rectangle};
	static enum ObjectType { Dynamic, Static};
	WorldObject(b2World& world, const WorldObject::ObjectShape shape, WorldObject::ObjectType type, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;

		//switch (type)
		//{
		//case Dynamic:
		//{
		//	bodyDef.type = b2_dynamicBody;
		//	fixture.density = 1.0f;
		//	break;
		//}
		//case Static:
		//{
		//	bodyDef.type = b2_staticBody;
		//	fixture.density = 0.0f;
		//	break;
		//}
		//}

		bodyDef.type = b2_staticBody;
		fixture.density = 0.0f;

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.3f;
		fixture.restitution = 0.f;

		switch (shape)
		{
		case EquilateralTriangle:
		{
			float sizeInPixels = widthInPixels;
			float sizeInMKS = sizeInPixels / SCALE;
			const int pointCount = 3;
			b2Vec2 points[pointCount] = { b2Vec2(sizeInMKS,0), b2Vec2(-sizeInMKS,sizeInMKS), b2Vec2(-sizeInMKS,-sizeInMKS) };
			
			b2PolygonShape bodyShape;
			bodyShape.Set(points, pointCount);
			fixture.shape = &bodyShape;
			physicalBody->CreateFixture(&fixture);

			renderShape.setPointCount(3);
			renderShape.setPoint(0, sf::Vector2f((points[0].x * SCALE), (points[0].y * SCALE)));
			renderShape.setPoint(1, sf::Vector2f((points[1].x * SCALE), (points[1].y * SCALE)));
			renderShape.setPoint(2, sf::Vector2f((points[2].x * SCALE), (points[2].y * SCALE)));
			renderShape.setFillColor(color);
			renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
			renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));
			break;
		}
		case Square:
		{
			float sizeInPixels = widthInPixels;
			float sizeInMKS = sizeInPixels / SCALE;
			
			b2PolygonShape bodyShape;
			bodyShape.SetAsBox(sizeInMKS / 2.f, sizeInMKS / 2.f);
			fixture.shape = &bodyShape;
			physicalBody->CreateFixture(&fixture);

			renderShape.setPointCount(4);
			renderShape.setPoint(0, sf::Vector2f(0.f, 0.f));
			renderShape.setPoint(1, sf::Vector2f(sizeInPixels, 0.f));
			renderShape.setPoint(2, sf::Vector2f(sizeInPixels, sizeInPixels));
			renderShape.setPoint(3, sf::Vector2f(0.f, sizeInPixels));
			renderShape.setOrigin(sizeInPixels / 2.f, sizeInPixels / 2.f);
			renderShape.setFillColor(color);
			renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
			renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));
			break;
		}
		case Rectangle:
		default:
		{
			float widthInMKS = widthInPixels / SCALE;
			float heightInMKS = heightInPixels / SCALE;
			
			b2PolygonShape bodyShape;
			bodyShape.SetAsBox(widthInMKS / 2.f, heightInMKS / 2.f);
			fixture.shape = &bodyShape;
			physicalBody->CreateFixture(&fixture);

			renderShape.setPointCount(4);
			renderShape.setPoint(0, sf::Vector2f(0.f, 0.f));
			renderShape.setPoint(3, sf::Vector2f(0.f, heightInPixels));
			renderShape.setPoint(2, sf::Vector2f(widthInPixels, heightInPixels));
			renderShape.setPoint(1, sf::Vector2f(widthInPixels, 0.f));
			renderShape.setOrigin(widthInPixels /2.f, heightInPixels / 2.f);
			renderShape.setFillColor(color);
			renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
			renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));
			break;
		}
		}
	}
	
	void positionUpdate();

	void imageRender(sf::RenderWindow& renderWindow);
	
	void GetPosition(std::string name);
};

class CircleWorldObject
{
private:
	b2Body* physicalBody;
	sf::CircleShape renderShape;
public:
	static enum ObjectType { Dynamic, Static };
	CircleWorldObject(b2World& world, CircleWorldObject::ObjectType type, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;

		//switch (type)
		//{
		//case Static:
		//{
		//	bodyDef.type = b2_staticBody;
		//	fixture.density = 0.0f;
		//	break;
		//}
		//case Dynamic:
		//default:
		//{
		//	bodyDef.type = b2_dynamicBody;
		//	fixture.density = 1.0f;
		//	break;
		//}
		//}

		bodyDef.type = b2_dynamicBody;
		fixture.density = 1.0f;

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = 0;
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.3f;
		fixture.restitution = 0.5f;

		float widthInMKS = widthInPixels / SCALE;
		float heightInMKS = heightInPixels / SCALE;

		b2CircleShape bodyShape;
		bodyShape.m_p.Set(xPos, yPos);
		bodyShape.m_radius = widthInMKS / 2.f;
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(widthInPixels / 2.f, widthInPixels / 2.f);
		renderShape.setRadius(widthInPixels / 2.f);
		renderShape.setPointCount(10);
		renderShape.setOutlineColor(color);
		renderShape.setOutlineThickness(-5);
		renderShape.setFillColor(sf::Color::Black);
		renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
	}
	void positionUpdate();

	void imageRender(sf::RenderWindow& renderWindow);

	void GetPosition(std::string name);
};

#endif