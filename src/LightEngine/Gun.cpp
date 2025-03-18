#include "Gun.h"
#include "Player.h"
#include "Water.h"
#include "TestScene.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Gun::OnInitialize()
{
	SetTag(TestScene::TGun); 
	mHitbox.isActive = false;
	SetRigidBody(false);

	mMaxAmmos = 4;
	mAmmos = mMaxAmmos;
	mReloadTime = 1.f;
	mDelayBeforeReloading = 2.f;

	mShootingDelay = 0.5f;
	mIsEquiped = true;
}

void Gun::OnUpdate()
{
	if (!pOwner)
		return;

	ReloadManager();

	if (mIsEquiped == false)
	{
		ChangeColor(sf::Color(255, 255, 255, 0));
		return;
	}

	sf::Vector2f playerPos = pOwner->GetPosition();
	sf::Vector2f pos = this->GetPosition();

	ChangeColor(sf::Color(255, 255, 255, 255));

	sf::Vector2f finalDirection = { std::cos(mAngle) * pOwner->GetSide(), std::sin(mAngle)};

	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z); // pos vertical du joystick droit

	if (mDirection.y >= -0.995)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || y < -25)
		{
			mAngle -= 2 * GetDeltaTime();
		}
	}

	if (mDirection.y <= 0.995)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || y > 25)
		{
			mAngle += 2 * GetDeltaTime();
		}
	}

	SetDirection(finalDirection.x, finalDirection.y);
	ShootManager(sf::Keyboard::Key::Right, 0, 7);
}

void Gun::Shoot()
{
	if (mAmmos <= 0)
		return;

	mProgressDelay = 0.f;

	sf::Vector2f pos = GetPosition();

	Water* w = CreateEntity<Water>({24, 24}, sf::Color::Blue);
	w->SetPosition(pos.x, pos.y);
	w->SetDirection(mDirection.x, mDirection.y); 
	mShootingDelay = 0.5f;

	AddRemoveAmmo(-1);
}
