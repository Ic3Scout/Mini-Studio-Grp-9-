#include "Player.h"
#include "Gun.h"
#include "WeedKiller.h"
#include "Weapon.h"

#include <iostream>

void Player::MoveRight(float deltaTime)
{
	//std::cout << "Player::MoveRight" << std::endl;

	mSpeed += mParameters.mAcceleration* deltaTime;
	if (mSpeed > mParameters.mMaxSpeed)
	{
		mSpeed = mParameters.mMaxSpeed;
	}
	SetPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
}

void Player::MoveLeft(float deltaTime)
{
	//std::cout << "Player::MoveLeft" << std::endl;

	mSpeed += mParameters.mAcceleration * deltaTime;
	if (mSpeed > mParameters.mMaxSpeed)
	{
		mSpeed = mParameters.mMaxSpeed;
	}
	SetPosition(GetPosition().x - mSpeed * deltaTime, GetPosition().y);
}

void Player::Jump()
{
	//std::cout << "Player::Jump" << std::endl;

	mHitbox.face = CollideWith::Nothing;

	mGravitySpeed = -std::sqrt(2 * mGravityAcceleration * GetRadius()*3); // mettre taille de la hitbox au lieu de l'entity ?
}

void Player::BasicControls()
{
	SetGravity(true);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1))// bouton X
	{
		if (mHitbox.face == CollideWith::Bottom)
		{
			Jump();
		}
	}

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
  
	if (GetPosition().y > 800)
	{
		SetPosition(641, 594);
	}
}

void Player::OnCollision(Entity* other)
{

	switch (mHitbox.face)
	{
	case CollideWith::Bottom:
		SetGravity(false);
		SetPosition(GetPosition().x, GetPosition().y - 0.5);
		break;

	case CollideWith::Top:
		mGravitySpeed = 0.f;
		SetPosition(GetPosition().x, GetPosition().y + 0.3);
		break;

	case CollideWith::Left:
		mSpeed = 0.f;
		SetPosition(GetPosition().x + 1, GetPosition().y);
		break;

	case CollideWith::Right:
		mSpeed = 0.f;
		SetPosition(GetPosition().x - 1, GetPosition().y);
		break;

	case CollideWith::Nothing:
		break;

	default:
		std::cout << "Bug\n";
		break;
	}
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
