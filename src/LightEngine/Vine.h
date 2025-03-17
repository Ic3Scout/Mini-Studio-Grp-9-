#pragma once
#include "Ally.h"

class Vine : public Ally
{
	bool grown = false;
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void Grow();
	void Retract();
};