#pragma once
#include "Entity.h"

class Player : public Entity
{
	float mSpeed = 0.f;
	float mAccelerationR = 10.f;
	float mAccelerationL = 10.f;
	float mMaxSpeed = 25.f;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnCollision(Entity* other) override;
};
