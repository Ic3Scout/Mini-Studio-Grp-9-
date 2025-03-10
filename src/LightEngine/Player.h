#pragma once
#include "Entity.h"

class Player : public Entity
{
	float mSpeed = 15.f;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnCollision(Entity* other) override;
};
