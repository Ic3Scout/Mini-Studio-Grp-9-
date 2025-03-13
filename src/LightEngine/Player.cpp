#include "Player.h"
#include "Gun.h"
#include "WeedKiller.h"
#include "Weapon.h"

#include <iostream>

void Player::BasicControls()
{
	float dt = GetDeltaTime();

	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

	if (sf::Joystick::isConnected(0))
	{
		//std::cout << "JoyStick Connecte" << std::endl;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || x > 25)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			mSpeed = 0.f;
		}
		MoveRight(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || x < -25)
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1))
	{
		Jump();
	}
}

void Player::MoveRight(float deltaTime)
{
	mSide = 2;
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
	mSide = 1;
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

void Player::OnInitialize()
{
	Weapon* gun = CreateEntity<Gun>(10, sf::Color::Magenta);
	gun->SetOwner(this);

	Weapon* weedKiller = CreateEntity<WeedKiller>(10, sf::Color::Yellow);;
	weedKiller->SetOwner(this);

	mWeapons.push_back(gun);
	mWeapons.push_back(weedKiller);
}

void Player::OnUpdate()
{
	BasicControls();

	SwapManager();
}

void Player::OnCollision(Entity* other)
{

}

void Player::SwapManager()
{
	if (mDelayToSwap >= 1.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			SwapWeapon();
		}
	}
	else
	{
		mDelayToSwap += GetDeltaTime();
	}
}

void Player::SwapWeapon()
{
	mDelayToSwap = 0.f;

	auto it = mWeapons.begin();

	for (it; it < mWeapons.end(); ++it)
	{
		if ((*it)->GetIsEquiped())
		{
			(*it)->SetIsEquiped(false);

			if (it == mWeapons.end() - 1)
			{
				it = mWeapons.begin();

				(*it)->SetIsEquiped(true);
			}
			else
			{
				(*(it + 1))->SetIsEquiped(true);
			}
			break;
		}
	}
}
