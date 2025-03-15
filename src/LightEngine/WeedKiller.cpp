#include "WeedKiller.h"
#include "Player.h"
#include "Acid.h"
#include "TestScene.h"

void WeedKiller::OnInitialize()
{
	SetTag(GetScene<TestScene>()->TWeedKiller); 
	mHitbox.isActive = false;
	SetRigidBody(false);

	mShootingDelay = 0.025f;

	mMaxAmmos = 100;
	mAmmos = mMaxAmmos;
	mReloadTime = 0.025f;

	mDelayBeforeReloading = 3.f;
}

void WeedKiller::OnUpdate()
{
	ReloadManager();

	if (mIsEquiped == false)
	{
		ChangeColor(sf::Color(255, 255, 0, 0));
		return;
	}

	if (!pOwner)
		return;

	system("cls");
	std::cout << "WeedKiller : " << mAmmos << "/" << mMaxAmmos << std::endl;

	ChangeColor(sf::Color(255, 255, 0, 255));

	sf::Vector2f playerPos = pOwner->GetPosition();

	SetPosition(playerPos.x + pOwner->GetSize().x * 0.5f * pOwner->GetSide(), playerPos.y);

	ShootManager(sf::Keyboard::Key::Right, 0, 7);
}

void WeedKiller::Shoot()
{
	if (mAmmos <= 0)
		return;

	mProgressDelay = 0.f;

	Acid* a = CreateEntity<Acid>(5, sf::Color::Green);
	a->SetOwner(this);
	a->SetPlayerSide(pOwner->GetSide());

	mShootingDelay = 0.025f;

	AddRemoveAmmo(-1);
}
