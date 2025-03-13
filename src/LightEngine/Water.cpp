#include "Water.h"
#include "Player.h"

void Water::OnUpdate()
{
	mProgress += GetDeltaTime();

	if(mProgress >= mSurvivalTime)
		Destroy();
}

void Water::OnCollision(Entity* collidedWith)
{
}

void Water::OnInitialize()
{
	SetRigidBody(false);

	SetSpeed(500);

	SetHitbox(GetRadius() * 2.f, GetRadius() * 2.f);
}

void Water::OnDestroy()
{
}