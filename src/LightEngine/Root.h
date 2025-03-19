#pragma once
#include "Obstacle.h"
class Root : public Obstacle
{
public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
};