#pragma once
#include"Enemy.h"

#define FONGUS_HP 2

class Fongus : public  Enemy
{
	float mActionTimer = 3.f;
	float mCooldownTimer = 0.f;
	int mActionState = 0;
	bool toxic = false;

public:
	Fongus();

	void OnInitialize() override;
	void  OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	void HandleActions();
};