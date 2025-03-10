#pragma once
#include "Entity.h"

class Player : public Entity
{
	float mSpeed = 0.f;
	float mAccelerationR = 1.f;
	float mAccelerationL = 1.f;
	float mMaxSpeed = 75.f;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnCollision(Entity* other) override;
};
