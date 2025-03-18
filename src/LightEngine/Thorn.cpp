#include "Thorn.h"
#include"TestScene.h"

void Thorn::OnInitialize()
{
	Enemy::OnInitialize;
	SetTag(TagEnemy::TThorn);
	mMaxHP = 1;
	mIsDead = false;
}

void Thorn::OnCollision(Entity* collidedWith)
{ 
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		AddRemoveHP(-1);
	}
}

void Thorn::OnUpdate()
{
	if (mIsDead)
	{
		Destroy();
	}
}