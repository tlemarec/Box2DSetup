#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "WorldObject.h"

#define SCALE 30.f

void WorldObject::update()
{
	renderShape.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
	renderShape.setRotation((physicalBody->GetAngle() * (180.0f / b2_pi)));
}

void WorldObject::render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(renderShape);
}
void WorldObject::GetPosition() {
	b2Vec2 position = physicalBody->GetPosition();
	printf("xPos : %4.2f meters, yPos : %4.2f meters\n", position.x, position.y);
}