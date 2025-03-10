#include "Player.h"

#include <iostream>

void Player::MoveRight(float deltaTime)
{
	std::cout << "Player::MoveRight" << std::endl;

	mSpeed += mAccelerationR * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	SetPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
}

void Player::MoveLeft(float deltaTime)
{
	std::cout << "Player::MoveLeft" << std::endl;

	mSpeed -= mAccelerationL * deltaTime;
	if (mSpeed < -mMaxSpeed)
		mSpeed = -mMaxSpeed;

	SetPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
}

void Player::Jump()
{
	//SetImpulsion(500.f);  (apres la physique)
}

void Player::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}
