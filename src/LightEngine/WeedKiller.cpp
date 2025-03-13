#include "WeedKiller.h"
#include "Player.h"
#include "Acid.h"

void WeedKiller::OnUpdate()
{
	if (!pOwner)
		return;

	sf::Vector2f playerPos = pOwner->GetPosition();

	SetPosition(playerPos.x, playerPos.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		if (mDelay <= 0)
		{
			Acid* a = CreateEntity<Acid>(5, sf::Color::Green);
			a->SetPosition(playerPos.x + pOwner->GetRadius(), playerPos.y);
			mDelay = 0.1f;
		}
	}

	if (mDelay < 0)
	{
		mDelay = 0;
	}
	else
		mDelay -= GetDeltaTime();

}

void WeedKiller::OnCollision(Entity* collidedWith)
{
}

void WeedKiller::OnInitialize()
{
	SetRigidBody(false);

}

void WeedKiller::OnDestroy()
{
}
