#include "Water.h"
#include "Player.h"
#include "TestScene.h"
#include "AssetManager.h"
#include "Animation.h"

void Water::OnUpdate()
{
	mProgress += GetDeltaTime();

	if(mProgress >= mSurvivalTime)
		Destroy();
}

void Water::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TPlayer)) 
		return;

	Destroy();
}

void Water::OnInitialize()
{
	SetTag(TestScene::TWater);

	SetRigidBody(false);

	SetSpeed(750);

	SetHitbox(GetSize().x, GetSize().y);

	LoadAnimation();
}

void Water::OnDestroy()
{
	GetScene<TestScene>()->GetAssetManager()->GetSound("Waterdrop")->play();
}

void Water::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Water.json");
	SetTexture("Water");
	mAnimations->LoadAnimationByRow("Water");
}
