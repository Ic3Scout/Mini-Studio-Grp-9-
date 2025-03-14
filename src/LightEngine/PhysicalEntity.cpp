#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
	std::cout << "collision" << std::endl;
	switch (mHitbox.face)
	{
	case CollideWith::Bottom:
		break;

	case CollideWith::Top:
		break;

	case CollideWith::Left:
		break;

	case CollideWith::Right:
		break;

	case CollideWith::Nothing:
		break;

	default:
		std::cout << "Bug\n";
		break;
	}

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
