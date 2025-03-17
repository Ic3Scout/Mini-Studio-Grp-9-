
#include "Fongus.h"
#include "TestScene.h"

void Fongus::OnInitialise()
{
	mMaxHP = 2;
	mIsDead = false;
}

void Fongus::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		fg->AddRemoveHP(-1);
	}
}

void Fongus::OnUpdate()
{
	if (mIsDead)
	{
		Destroy();
	}
}
