#include "Bramble.h"
#include"TestScene.h"

void Bramble::OnInitialize()
{
	SetTag(TestScene::TBramble);
	mMaxHP = 1;
	mIsDead = false;
}

void Bramble::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		AddRemoveHP(-1);
	}
}

void Bramble::OnUpdate()
{

	if (mIsDead)
	{
		Destroy();
	}
}


