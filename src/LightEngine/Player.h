#pragma once
#include "PhysicalEntity.h"

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mMaxSpeed = 300.f;
	float mAcceleration = 800.f;
	float mDeceleration = 125.f;
	float mJumpSpeed = -400.f;
};

class Player : public PhysicalEntity
{
	PlayerParameter mParameters;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};
