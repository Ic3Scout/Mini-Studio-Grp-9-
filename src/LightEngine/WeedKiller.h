#pragma once
#include "Entity.h"

class Player;

class WeedKiller : public Entity
{
	Player* pOwner;

	int mAmmos = 100;

	float mDelay = 0.1f;
public:
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;

	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
};

