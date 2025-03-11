#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
	// A SUPPRIMER C JUSTE DU DEBUGAGE

	system("cls");

	switch (IsColliding(collidedWith))
	{
	case CollideWith::Bottom:
		std::cout << "Collision bas\n";
		break;

	case CollideWith::Top:
		std::cout << "Collision haut\n";
		break;

	case CollideWith::Left:
		std::cout << "Collision gauche\n";
		break;

	case CollideWith::Right:
		std::cout << "Collision droite\n";
		break;

	default:
		std::cout << "Collision buguee\n";
		break;
	}

	// TOUT CA

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
