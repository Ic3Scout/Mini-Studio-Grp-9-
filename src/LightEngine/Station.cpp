#include "Station.h"
#include "Animation.h"

void Station::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TStation);
	SetRigidBody(false);
	mShape.setSize({ 75.f, 150.f});
	SetHitbox(GetSize().x, GetSize().y);

	mAnimations = new Animation();
	LoadAnimation();
}

void Station::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Station.json");
	SetTexture("Station");
	mAnimations->LoadAnimationSingle("Idle");
}
