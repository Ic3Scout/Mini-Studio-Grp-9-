#pragma once
#include "Enemy.h"
class Bramble : public  Enemy
{
	
public:

	void OnInitialize() override;
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};


