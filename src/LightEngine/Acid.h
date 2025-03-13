#pragma once
#include "Entity.h"

class Acid : public Entity
{
	float mSurvivalTime = 0.1f;
	float mProgress = 0.f;
public:
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;
};

