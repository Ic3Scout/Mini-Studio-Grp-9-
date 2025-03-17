#pragma once
#include " Ennemy.h"
class  Bramble : public Ennemy
{
	Bramble* br;
public:
	void OnInitialise();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};

