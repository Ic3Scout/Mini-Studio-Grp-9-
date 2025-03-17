#include " Bramble.h"
#include "TestScene.h"

void Fongus::OnInitialise()
{
	mMaxHP = 1;
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
	if (IsDead)
	{
		Destroy();
	}
}
