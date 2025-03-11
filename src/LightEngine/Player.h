#pragma once
#include "PhysicalEntity.h"

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 150.f;
	float mDeceleration = 125.f;
	float mJumpSpeed = 200.f;
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
