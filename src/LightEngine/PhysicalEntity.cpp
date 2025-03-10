#include "PhysicalEntity.h"

void PhysicalEntity::Fall(float dt)
{
	sf::Vector2f pos = GetPosition();

	mGravitySpeed += mGravityAcceleration * dt;

	float newPosY = pos.y + mGravitySpeed * dt;
	this->SetPosition(pos.x, newPosY);
}
