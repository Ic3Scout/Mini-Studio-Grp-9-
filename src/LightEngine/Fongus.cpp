
#include "Fongus.h"
#include "TestScene.h"

void Fongus::OnInitialize()
{
	//SetTag(TestScene::TFongus);
	mMaxHP = 2;
	mIsDead = false;
}

void Fongus::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		AddRemoveHP(-1);
	}
}

void Fongus::OnUpdate()
{
	if (mIsDead)
	{
		Destroy();
	}
}
