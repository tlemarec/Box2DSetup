#include <stdio.h>
#include <iostream>
#include "WorldObject.h"

#define SCALE 30.f

//WorldObject
void WorldObject::getPosition(std::string name) 
{
	b2Vec2 position = physicalBody->GetPosition();
	std::cout << name << ", xPos : " << position.x << ", yPos : " << position.y << std::endl;
}
b2Body* WorldObject::getPhysicalBody()
{
	return physicalBody;
}

//ConvexWorldObject
void ConvexWorldObject::positionUpdate()
{
	renderShape.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
	renderShape.setRotation((physicalBody->GetAngle() * (180.0f / b2_pi)));
}
void ConvexWorldObject::imageRender(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(renderShape);
}

//CircleWorldObject
void CircleWorldObject::positionUpdate()
{
	renderShape.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
	renderShape.setRotation((physicalBody->GetAngle() * (180.0f / b2_pi)));
}
void CircleWorldObject::imageRender(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(renderShape);
}

//RectangleWorldObject
void RectangleWorldObject::positionUpdate()
{
	renderShape.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
	renderShape.setRotation((physicalBody->GetAngle() * (180.0f / b2_pi)));
}
void RectangleWorldObject::imageRender(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(renderShape);
}