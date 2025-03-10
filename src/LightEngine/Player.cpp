#include "Player.h"

#include <iostream>

void Player::MoveRight(float deltaTime)
{
	std::cout << "Player::MoveRight" << std::endl;

	SetPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
}

void Player::MoveLeft(float deltaTime)
{
    std::cout << "Player::MoveLeft" << std::endl;

    SetPosition(GetPosition().x - mSpeed * deltaTime, GetPosition().y); // Correction ici
}

void Player::Jump()
{
	//SetImpulsion(500.f);  (apres la physique)
}

void Player::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}