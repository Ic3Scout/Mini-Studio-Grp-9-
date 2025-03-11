#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
	std::cout << "Oof\n";
}

void PhysicalEntity::Fall(float dt)
{
	if (mGravity == false)
	{
		mGravitySpeed = 0.f;

		return;
	}

	mGravitySpeed += mGravityAcceleration * dt;

	/*mDirection.y = 1;

	mSpeed = mGravitySpeed;*/

	sf::Vector2f pos = GetPosition();
	float newPosY = pos.y + mGravitySpeed * dt;
	SetPosition(pos.x, newPosY);
}
