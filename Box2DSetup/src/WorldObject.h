#ifndef pgcdHPP
#define pgcdHPP

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.f

class WorldObject 
{
private:
	b2Body * physicalBody;

public:
	static enum ObjectShape { EquilateralTriangle };
	static enum ObjectType { Dynamic, Static };

	//void positionUpdate();

	//void imageRender(sf::RenderWindow& renderWindow);

	void getPosition(std::string name);

	b2Body* getPhysicalBody();

};

class ConvexWorldObject
{
private:
	b2Body* physicalBody;
	sf::ConvexShape renderShape;

public:
	static enum ObjectShape { EquilateralTriangle};
	static enum ObjectType { Dynamic, Static};
	ConvexWorldObject(b2World& world, const ConvexWorldObject::ObjectShape shape = ConvexWorldObject::ObjectShape::EquilateralTriangle, ConvexWorldObject::ObjectType type = ConvexWorldObject::ObjectType::Dynamic, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;

		switch (type)
		{
		case Dynamic:
		{
			bodyDef.type = b2_dynamicBody;
			fixture.density = 1.0f;
			break;
		}
		case Static:
		{
			bodyDef.type = b2_staticBody;
			fixture.density = 0.0f;
			break;
		}
		}

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;

		switch (shape)
		{
		case EquilateralTriangle:
		default:
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
		}
	}
	
	void positionUpdate();

	void imageRender(sf::RenderWindow& renderWindow);
	
	void getPosition(std::string name);

	b2Body* getPhysicalBody();

};

class CircleWorldObject
{
private:
	b2Body * physicalBody;
	sf::CircleShape renderShape;

public:
	static enum ObjectType { Dynamic, Static };
	CircleWorldObject(b2World& world, CircleWorldObject::ObjectType type = CircleWorldObject::ObjectType::Dynamic, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;

		switch (type)
		{
		case Dynamic:
		default:
		{
			bodyDef.type = b2_dynamicBody;
			fixture.density = 1.0f;
			break;
		}
		case Static:
		{
			bodyDef.type = b2_staticBody;
			fixture.density = 0.0f;
			break;
		}
		}

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;

		float widthInMKS = widthInPixels / SCALE;
		float heightInMKS = heightInPixels / SCALE;

		b2CircleShape bodyShape;
		bodyShape.m_radius = widthInMKS / 2.f;
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(widthInPixels / 2.f, heightInPixels / 2.f);
		renderShape.setRadius(widthInPixels / 2.f);
		renderShape.setPointCount(50);
		renderShape.setOutlineColor(color);
		renderShape.setOutlineThickness(-5.f);
		renderShape.setFillColor(color);

		renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
		renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));

		
	}

	void positionUpdate();

	void imageRender(sf::RenderWindow& renderWindow);

	void getPosition(std::string name);

	b2Body* getPhysicalBody();

};

class RectangleWorldObject
{
private:
	b2Body* physicalBody;
	sf::RectangleShape renderShape;

public:
	static enum ObjectType { Dynamic, Static };
	RectangleWorldObject(b2World& world, RectangleWorldObject::ObjectType type = RectangleWorldObject::ObjectType::Dynamic, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f)
	{
		b2BodyDef bodyDef;
		b2FixtureDef fixture;

		switch (type)
		{
		case Dynamic:
		default:
		{
			bodyDef.type = b2_dynamicBody;
			fixture.density = 1.0f;
			break;
		}
		case Static:
		{
			bodyDef.type = b2_staticBody;
			fixture.density = 0.0f;
			break;
		}
		}

		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);

		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;

		float widthInMKS = widthInPixels / SCALE;
		float heightInMKS = heightInPixels / SCALE;

		b2PolygonShape bodyShape;
		bodyShape.SetAsBox(widthInMKS / 2.f, heightInMKS / 2.f);
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(widthInPixels / 2.f, heightInPixels / 2.f);
		renderShape.setFillColor(sf::Color::Transparent);
		renderShape.setSize(sf::Vector2f(widthInPixels, heightInPixels));
		renderShape.setOutlineColor(color);
		renderShape.setOutlineThickness(-5);
		renderShape.setFillColor(color);

		renderShape.setPosition((physicalBody->GetPosition().x * SCALE), (physicalBody->GetPosition().y * SCALE));
		renderShape.setRotation(physicalBody->GetAngle() * (180.0f / b2_pi));

	}
	
	void positionUpdate();

	void imageRender(sf::RenderWindow& renderWindow);

	void getPosition(std::string name);

	b2Body* getPhysicalBody();
};


#endif