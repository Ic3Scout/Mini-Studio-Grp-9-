#pragma once
#include "Obstacle.h"
class Wall : public Obstacle
{
public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
};