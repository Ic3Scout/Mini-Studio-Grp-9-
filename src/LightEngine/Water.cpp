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
	if (collidedWith->IsTag(GetScene<TestScene>()->TPlayer))
		return;

	Destroy();
}

void Water::OnInitialize()
{
	SetTag(GetScene<TestScene>()->TWater);

	SetRigidBody(false);

	SetSpeed(750);

	SetHitbox(GetRadius() * 2.f, GetRadius() * 2.f);
}

void Water::OnDestroy()
{
}