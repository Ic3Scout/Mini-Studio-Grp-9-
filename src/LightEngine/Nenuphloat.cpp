#include "Nenuphloat.h"
#include "TestScene.h"
#include "Player.h"

void Nenuphloat::OnInitialize()
{
	mKineticBody = false;
	Ally::OnInitialize();
	SetTagAlly(TNenuphloatR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Nenuphloat::OnUpdate()
{
	Ally::OnUpdate();

	if(grown && mProgress <= mDuration)
		mProgress += GetDeltaTime();

	if (grown && mProgress >= mDuration)
	{
		Retract();
	}
}

void Nenuphloat::FixedUpdate(float dt)
{

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
	SetRigidBody(true);
	SetTagAlly(TNenuphloatG);
	if (!grown)
	{
		grown = true;
		SetHitbox(GetSize().x * 5, GetSize().y);
	}
}

void Nenuphloat::Retract()
{
	SetRigidBody(false);
	SetTagAlly(TNenuphloatR);
	if (!grown)
		return;
	grown = false;
	SetHitbox(GetSize().x, GetSize().y);

	mProgress = 0.f;
}