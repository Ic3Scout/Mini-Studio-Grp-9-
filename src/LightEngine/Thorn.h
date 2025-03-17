#pragma once
#include "Ennemy.h"
class Thorn: public  Ennemy
{
	Thorn* th;
public:

	void OnInitialise();
	void  OnCollision(Entity* collidedWith);
	void OnUpdate();
};

