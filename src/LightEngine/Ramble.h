#pragma once
#include "Ennemy.h"
class  Bramble : public Ennemy
{
	
public:
	void OnInitialize();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};

