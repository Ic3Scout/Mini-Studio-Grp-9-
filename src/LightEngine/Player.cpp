#include "Player.h"

#include <iostream>

void Player::MoveRight(float deltaTime)
{
	std::cout << "Player::MoveRight" << std::endl;

	mSpeed += mParameters.mAcceleration* deltaTime;
	if (mSpeed > mParameters.mMaxSpeed)
	{
		mSpeed = mParameters.mMaxSpeed;
	}
	SetPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
}

void Player::MoveLeft(float deltaTime)
{
	std::cout << "Player::MoveLeft" << std::endl;

	mSpeed += mParameters.mAcceleration * deltaTime;
	if (mSpeed > mParameters.mMaxSpeed)
	{
		mSpeed = mParameters.mMaxSpeed;
	}
	SetPosition(GetPosition().x - mSpeed * deltaTime, GetPosition().y);
}

void Player::Jump()
{
	//SetImpulsion(500.f);  (apres la physique)
}

void Player::OnUpdate()
{
	float dt = GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		MoveRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		MoveLeft(dt);
	}
}

void Player::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}