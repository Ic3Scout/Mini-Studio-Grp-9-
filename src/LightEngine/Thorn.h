#pragma once
#include "Enemy.h"
class Thorn: public Enemy
{
public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
};

