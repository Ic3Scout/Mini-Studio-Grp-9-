#pragma once
#include "Entity.h"
class End : public Entity
{
	bool isTriggered = false;
	float mAnimationDuration = 3.f;
	float mProgress = 0.f;

	bool isAnimationTriggered = false;
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override;
	void OnCollision(Entity* pOther) override;
};

