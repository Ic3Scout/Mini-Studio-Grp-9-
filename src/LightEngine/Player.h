#pragma once
#include "Entity.h"

class Player : public Entity
{
	float mSpeed = 200.f;

public:
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};
