#pragma once
#include "Entity.h"

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 25.f;
	float mDeceleration = 75.f;
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
