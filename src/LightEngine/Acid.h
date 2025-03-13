#pragma once
#include "Entity.h"

class WeedKiller;

class Acid : public Entity
{
	WeedKiller* pOwner;
	int mPlayerSide = 1;
	float mSurvivalTime = 0.1f;
	float mProgress = 0.f;
public:

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;
	
	void SetPlayerSide(int value) { mPlayerSide = value; }

	void SetOwner(WeedKiller* pWK);
};

