#include "Acid.h"
#include "WeedKiller.h"
#include "TestScene.h"
#include "Player.h"

void Acid::OnUpdate()
{
	if (pOwner == nullptr)
	{
		return;
	}

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
	SetTag(TestScene::TAcid); 
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

	if (pOwner != nullptr)
	{
		Player* p = pOwner->GetOwner();
		SetHitboxOffset(100 * p->GetSide(), 0);
		SetHitbox(200, 100);
	}
	else
	{
		pOwner = nullptr;
	}
}
