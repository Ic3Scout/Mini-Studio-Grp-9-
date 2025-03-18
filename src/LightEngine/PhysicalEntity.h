#pragma once
#include "Entity.h"
#define GRAVITY_ACCELERATION 9.81f * 50

class PhysicalEntity : public Entity
{
protected:
	bool mGravity = false;
	float mGravitySpeed = 0.f;

public:
	void FixedUpdate(float dt) override;
	void OnCollision(Entity* collidedWith) override;
	void SetGravity(bool value) { mGravity = value; }
	void SwapGravity() { mGravity = !mGravity; }
	void Fall(float dt);
};