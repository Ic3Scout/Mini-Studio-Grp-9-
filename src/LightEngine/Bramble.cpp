#include "Bramble.h"
#include"TestScene.h"

void Bramble::OnInitialise()
{
	mMaxHP = 1;
	mIsDead = false;
}

void Bramble::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		br->AddRemoveHP(-1);
	}
}

void Bramble::OnUpdate()
{

	if (mIsDead)
	{
		Destroy();
	}
}


