#include "Acid.h"

void Acid::OnUpdate()
{
	mProgress += GetDeltaTime();

	if (mProgress >= mSurvivalTime)
		Destroy();
}

void Acid::OnCollision(Entity* collidedWith)
{
}

void Acid::OnInitialize()
{
	SetRigidBody(false);
	SetHitbox(200, 50);
	SetHitboxOffset(100, 0);
}

void Acid::OnDestroy()
{
}
