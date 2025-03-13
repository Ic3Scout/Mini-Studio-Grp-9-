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
	
	/*
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

	if (sf::Joystick::isConnected(0))
	{
		std::cout << "JoyStick Connecte" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		std::cout << "X Pressed 1" << std::endl;

		Jump();
	}
	if (sf::Joystick::isButtonPressed(0, 2))
	{
		std::cout << "O Pressed 2" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0, 3))
	{
		std::cout << "tri Pressed 3" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0, 4))
	{
		std::cout << "car Pressed 4" << std::endl;
	}
	if (x > 25)
	{
		MoveRight(dt);
	}
	else if (x < -25)
	{
		MoveLeft(dt);
	}
	else
	{
		mSpeed = 0.f;
	}
	std::cout << "axe X" << x << std::endl;
	*/
	



	
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