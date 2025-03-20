#pragma once
#include "Ally.h"

class Bulb : public Ally
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;

	void FixedUpdate(float dt) override;

	void LoadAnimation() override;
};