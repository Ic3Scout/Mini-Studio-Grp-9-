#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
protected:
	bool mGravity = false;
	float mGravitySpeed = 0;
	float mGravityAcceleration = 9.81f * 25;

public:
	void OnCollision(Entity* collidedWith) override;
	void SetGravity(bool value) { mGravity = value; }
	void SwapGravity() { mGravity = !mGravity; }
	void Fall(float dt);
};

