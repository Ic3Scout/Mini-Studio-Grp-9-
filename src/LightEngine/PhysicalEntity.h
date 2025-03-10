#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
protected:
	float mGravitySpeed = 0;
	float mGravityAcceleration = 9.81f;

public:

	void Fall(float dt);
};

