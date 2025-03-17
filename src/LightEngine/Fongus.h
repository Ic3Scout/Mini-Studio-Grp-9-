#pragma once
#include"Ennemy.h"
class Fongus : public  Ennemy
{
	Fongus* fg;
public:
	void OnInitialise();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};

