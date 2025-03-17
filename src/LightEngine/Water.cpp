#include "Water.h"
#include "Player.h"
#include "TestScene.h"

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
}

void Water::OnDestroy()
{
}