#include <stdio.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "WorldObject.h"

#define SCALE 30.f

//WorldObject
void WorldObject::positionUpdate()
{
	renderShape.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
	renderShape.setRotation((physicalBody->GetAngle() * (180.0f / b2_pi)));
}

void WorldObject::imageRender(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(renderShape);
}
void WorldObject::GetPosition(std::string name) {
	b2Vec2 position = physicalBody->GetPosition();	
	std::cout << name << ", xPos : " << position.x << ", yPos : " << position.y << std::endl;
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
void CircleWorldObject::GetPosition(std::string name) {
	b2Vec2 position = physicalBody->GetPosition();
	std::cout << name << ", xPos : "  << position.x << ", yPos : " << position.y << std::endl;
}