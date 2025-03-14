#include "Acid.h"
#include "WeedKiller.h"

void Acid::OnUpdate()
{
	if (!pOwner)
		return;

	int mFactor = 1;

	if (mPlayerSide == 1)
	{
		mFactor = -1;
	}

	SetHitboxOffset(100 * mFactor, 0);
	SetHitbox(200, 100);

	sf::Vector2f wkPos = pOwner->GetPosition();

	SetPosition(wkPos.x, wkPos.y);
	mProgress += GetDeltaTime();

	if (mProgress >= mSurvivalTime)
		Destroy();
}

void Acid::OnCollision(Entity* collidedWith)
{
}

void Acid::OnInitialize()
{
}

void Acid::OnDestroy()
{
}

void Acid::SetOwner(WeedKiller* pWK)
{
	pOwner = pWK;

	sf::Vector2f wkPos = pOwner->GetPosition();

	SetPosition(wkPos.x, wkPos.y);
	SetRigidBody(false);
}
