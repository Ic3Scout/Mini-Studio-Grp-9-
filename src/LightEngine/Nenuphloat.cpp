#include "Nenuphloat.h"
#include "TestScene.h"

void Nenuphloat::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TNenuphloatR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Nenuphloat::OnUpdate()
{
	if(grown && mProgress <= mDuration)
		mProgress += GetDeltaTime();

	if (grown && mProgress >= mDuration)
	{
		Retract();
	}
}

void Nenuphloat::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		Grow();
	}
}

void Nenuphloat::Grow()
{
	SetTagAlly(TNenuphloatG);
	if (!grown)
	{
		grown = true;
		SetHitbox(GetSize().x * 5, GetSize().y);
	}
}

void Nenuphloat::Retract()
{
	SetTagAlly(TNenuphloatR);
	if (!grown)
		return;
	grown = false;
	SetHitbox(GetSize().x, GetSize().y);

	mProgress = 0.f;
}