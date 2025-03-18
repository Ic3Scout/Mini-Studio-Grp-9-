#pragma once
#include "Enemy.h"

#define THORN_HP 4

class Thorn: public Enemy
{
	float mDuration = 2.f;
	float mProgress = 0.f;

	bool isActive = false;
public:
	Thorn();

	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
};

