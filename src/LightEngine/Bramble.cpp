#include "Bramble.h"
#include"TestScene.h"

Bramble::Bramble() : Enemy(BRAMBLE_HP) {}

void Bramble::OnInitialize()
{
	SetTagEnemy(Enemy::TBramble);
	mIsDead = false;
	mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;
}

void Bramble::OnCollision(Entity* collidedWith)
{
}

void Bramble::OnUpdate()
{
	bool isPlayerInProximity = IsPlayerInProximity();
	if (isPlayerInProximity)
	{
		mExplosionActive = true;
	}

	if (mExplosionActive)
	{
		mExplosionTimer += GetDeltaTime();
	}

	if (mExplosionTimer >= mExplosionDelay)
	{
		SetHitbox(GetSize().x * 5, GetSize().y * 5);
		if (isPlayerInProximity)
			player->AddRemoveHP(-2);
		AddRemoveHP(-1);
		mExplosionTimer = 0.f;
	}

	if (mIsDead)
	{
		Destroy();
	}
}

bool Bramble::IsPlayerInProximity()
{
	sf::Vector2f playerPosition = player->GetPosition();
	sf::Vector2f thornPosition = GetPosition();

	float distance = std::sqrt(std::pow(playerPosition.x - thornPosition.x, 2) + std::pow(playerPosition.y - thornPosition.y, 2));

	return distance <= mProximityRadius;
}