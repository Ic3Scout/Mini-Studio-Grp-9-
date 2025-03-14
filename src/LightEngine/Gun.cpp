#include "Gun.h"
#include "Debug.h"
#include "Player.h"
#include "Water.h"
#include "TestScene.h"
#include "Scene.h"
#include <iostream>

void Gun::OnInitialize()
{
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

	system("cls");
	std::cout << "Water Gun : " << mAmmos << "/" << mMaxAmmos << std::endl;

	ChangeColor(sf::Color(255, 0, 0, 255));

	sf::Vector2f playerPos = pOwner->GetPosition();

	int mFactor = 1;

	if (pOwner->GetSide() == 1)
	{
		mFactor = -1;
	}

	sf::Vector2f finalDirection = { std::cos(mAngle) * mFactor, std::sin(mAngle) };

	SetPosition(playerPos.x + pOwner->GetRadius() * finalDirection.x, playerPos.y + pOwner->GetRadius() * finalDirection.y);

	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R); // pos vertical du joystick droit

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

	float playerRadius = pOwner->GetRadius();

	Debug::DrawLine(playerPos.x + playerRadius * finalDirection.x, playerPos.y + playerRadius * finalDirection.y, playerPos.x + GetDirection().x * 300, playerPos.y + GetDirection().y * 300, sf::Color::White);
}

void Gun::Shoot()
{
	if (mAmmos <= 0)
		return;

	mProgressDelay = 0.f;

	sf::Vector2f pos = GetPosition();

	Water* w = CreateEntity<Water>(15, sf::Color::Blue);
	w->SetPosition(pos.x, pos.y);
	w->SetDirection(mDirection.x, mDirection.y);
	mShootingDelay = 0.5f;

	AddRemoveAmmo(-1);
}
