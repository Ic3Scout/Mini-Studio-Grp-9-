#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::OnUpdate()
{
	Fall(GetDeltaTime());
}

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
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
		mGravityAcceleration = 0;
		return;
	}

	mGravityAcceleration = GRAVITY_ACCELERATION;

	mGravitySpeed += mGravityAcceleration * dt;
	
	sf::Vector2f pos = GetPosition(); 
	float newPosY = pos.y + mGravitySpeed * dt;
	SetPosition(pos.x, newPosY);
}
