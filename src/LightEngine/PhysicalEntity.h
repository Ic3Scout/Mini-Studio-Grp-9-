#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
protected:
	bool mGravity = true;
	float mGravitySpeed = 0;
	float mGravityAcceleration = 9.81f * 25;

public:
	void SetGravity(bool value) { mGravity = value; }
	void SwapGravity() { mGravity = !mGravity; }
	void Fall(float dt);
};

