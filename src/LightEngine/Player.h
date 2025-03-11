#pragma once
#include "Entity.h"

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mMaxSpeed = 500.f;
	float mAcceleration = 300.f;
	float mDeceleration = 150.f;
};

class Player : public Entity
{
	PlayerParameter mParameters;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};
