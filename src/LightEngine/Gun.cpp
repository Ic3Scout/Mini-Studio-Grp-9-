#include "Gun.h"
#include "Debug.h"
#include "Player.h"
#include "Water.h"
#include <iostream>

void Gun::OnUpdate()
{
	if (!pOwner)
		return;

	sf::Vector2f playerPos = pOwner->GetPosition();

	SetPosition(playerPos.x, playerPos.y);

	sf::Vector2f dir = GetDirection();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mAngle -= 2 * GetDeltaTime();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mAngle += 2 * GetDeltaTime();
	}

	std::cout << mAngle << std::endl;

	SetDirection(std::cos(mAngle), std::sin(mAngle));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (mDelay <= 0)
		{
			Shoot();
		}
	}

	if (mDelay < 0)
	{
		mDelay = 0;
	}
	else
		mDelay -= GetDeltaTime();

	Debug::DrawLine(playerPos.x, playerPos.y, playerPos.x + GetDirection().x * 300, playerPos.y + GetDirection().y * 300, sf::Color::Red);
}

void Gun::Shoot()
{
	sf::Vector2f playerPos = pOwner->GetPosition();

	Water* w = CreateEntity<Water>(15, sf::Color::Blue);
	w->SetPosition(playerPos.x, playerPos.y);
	w->SetDirection(mDirection.x, mDirection.y);
	mDelay = 0.5f;
}
