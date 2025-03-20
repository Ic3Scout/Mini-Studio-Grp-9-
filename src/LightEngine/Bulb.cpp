#include "Bulb.h"
#include "Animation.h"
#include "TestScene.h"

void Bulb::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TBulb);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);

	LoadAnimation();
}

void Bulb::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		ChangeAnimation("Release", "single");
	}
}

void Bulb::FixedUpdate(float dt)
{
	if (mAnimations->IsFinished())
	{
		ChangeAnimation("Idle", "single");
	}
}

void Bulb::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Bulbe_Lumina.json");
	SetTexture("Bulb");
	mAnimations->LoadAnimationSingle("Idle");
}

void Bulb::OnUpdate()
{
	Ally::OnUpdate();
}
