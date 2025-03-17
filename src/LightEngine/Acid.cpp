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
		sf::Vector2f playerSize = p->GetSize();

		SetHitboxOffset(playerSize.x * p->GetSide(), 0);
		SetHitbox(playerSize.x * 2, playerSize.x);
	}
	else
	{
		pOwner = nullptr;
	}
}
