#pragma once
#include"Enemy.h"
class Fongus : public  Enemy
{
public:
	void OnInitialize();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};

