#include "Thorn.h"
#include"TestScene.h"

void Thorn::OnInitialise()
{
	mMaxHP = 1;
	mIsDead = false;
}

void Thorn::OnCollision(Entity* collidedWith)
{ 
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		th->AddRemoveHP(-1);
	}
}

void Thorn::OnUpdate()
{
	
	if (mIsDead)
	{
		Destroy();
	}
}

