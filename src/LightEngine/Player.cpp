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
	std::cout << "Player::Jump" << std::endl;

	mGravitySpeed = mParameters.mJumpSpeed;
}

void Player::OnUpdate()
{
	float dt = GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			mSpeed = 0.f;
		}
		MoveRight(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			mSpeed = 0.f;
		}
		MoveLeft(dt);
	}
	else
	{
		mSpeed = 0.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		Jump();
	}
}

void Player::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}