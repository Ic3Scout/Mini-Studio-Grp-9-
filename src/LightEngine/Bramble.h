#pragma once
#include "Enemy.h"

#define BRAMBLE_HP 1

class Bramble : public  Enemy
{
	float mExplosionDelay = 1.f;
	float mExplosionTimer = 0.f;
	bool mExplosionActive = false;
	float mProximityRadius = 0.f;
	bool isPlayerInProximity = false;
public:
	Bramble();

	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	bool IsPlayerInProximity();
	void Explose();
};