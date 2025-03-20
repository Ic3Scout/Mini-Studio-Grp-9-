#include "Bramble.h"
#include"TestScene.h"

Bramble::Bramble() : Enemy(BRAMBLE_HP) {}

void Bramble::OnInitialize()
{
	SetKineticBody(false);
	SetRigidBody(true);
	Enemy::OnInitialize(); 
	SetTagEnemy(Enemy::TBramble);
	mIsDead = false;
	mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;
}

void Bramble::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		Explose();
	}
}

void Bramble::OnUpdate()
{
	isPlayerInProximity = IsPlayerInProximity();
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
		Explose();
	}

	if (mIsDead)
	{
		Destroy();
	}
}

void Bramble::Explose()
{
	SetHitbox(GetSize().x * 5, GetSize().y * 5);
	if (isPlayerInProximity)
	{
		player->AddRemoveHP(-1);
		player->TransitionTo(Player::TakingDamage);
	}
	AddRemoveHP(-1);
	mExplosionTimer = 0.f;
}

bool Bramble::IsPlayerInProximity()
{
	sf::Vector2f playerPosition = player->GetPosition();
	sf::Vector2f thornPosition = GetPosition();

	float distance = std::sqrt(std::pow(playerPosition.x - thornPosition.x, 2) + std::pow(playerPosition.y - thornPosition.y, 2));

	return distance <= mProximityRadius;
}