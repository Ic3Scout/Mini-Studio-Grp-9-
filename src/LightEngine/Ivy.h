#pragma once
#include"Ennemy.h"
class Ivy : public  Ennemy
{
	Ivy* iv;
public:
	void OnInitialise();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};
