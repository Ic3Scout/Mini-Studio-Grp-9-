#include "Player.h"
#include "Gun.h"
#include "WeedKiller.h"
#include "Weapon.h"
#include "TestScene.h"
#include "Debug.h"
#include "AmmoBar.h"

#include <iostream>

void Player::MoveRight(float deltaTime)
{
	mSide = 1;

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
	mSide = -1;

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

	mGravitySpeed = -std::sqrt(2 * mGravityAcceleration * GetSize().y); // mettre taille de la hitbox au lieu de l'entity ?
}

void Player::BasicControls()
{
	SetGravity(true);

	float dt = GetDeltaTime();

	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);// pos horizontal du joystick gauche

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
	if (sf::Joystick::isButtonPressed(0, 0))
	{
		std::cout << "car Pressed 4" << std::endl;
	}

	bool isMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || x > 25)
	{
		isMoving = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || x < -25)
		{
			isMoving = false;
		}
		else
			MoveRight(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || x < -25)
	{
		isMoving = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || x > 25)
		{
			isMoving = false;
		}
		else
			MoveLeft(dt);
	}

	if (isMoving == false)
	{
		mSpeed = 0;
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
	SetTag((int) TestScene::TPlayer); 

	Weapon* gun = CreateEntity<Gun>(10, sf::Color::White);
	gun->SetOwner(this);

	Weapon* weedKiller = CreateEntity<WeedKiller>(10, sf::Color::Yellow);;
	weedKiller->SetOwner(this);

	mWeapons.push_back(gun);
	mWeapons.push_back(weedKiller);

	mBar = new AmmoBar();

	mBar->SetOwner(this);
}

void Player::OnUpdate()
{
	BasicControls();

	SwapManager();
	
	sf::Vector2f pos = GetPosition();

	for (Weapon* w : mWeapons)
	{
		w->SetPosition(pos.x + mSide * mHitbox.size.x * 0.5f, pos.y);

		if (w->IsTag(GetScene<TestScene>()->TGun) && w->GetIsEquiped() == true)
		{
			sf::Vector2f gunPos = w->GetPosition();
			sf::Vector2f gunDir = w->GetDirection();

			Debug::DrawLine(gunPos.x, gunPos.y, gunPos.x + gunDir.x * 300, gunPos.y + gunDir.y * 300, sf::Color::Red);
		}

		if (w->GetIsEquiped() == true)
		{
		}

	}

	mBar->UpdateBar(); 

	if (GetPosition().y > 800)
	{
		SetPosition(641, 594);
	}
}

void Player::OnCollision(Entity* other)
{
	if ( other->IsTag(TestScene::TWater) || other->IsTag(TestScene::TAcid) )
		return;

	switch (mHitbox.face)
	{
	case CollideWith::Bottom:
		mGravitySpeed = 0;
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
	if (mDelayToSwap >= 0.5f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) || sf::Joystick::isButtonPressed(0, 3))
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

Weapon* Player::GetCurrentEquipedWeapon()
{
	for (Weapon* w : mWeapons)
	{
		if (w->GetIsEquiped() == true)
			return w;
	}
}
