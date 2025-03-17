#include "Vine.h"
#include "TestScene.h"

void Vine::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TVineR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Vine::OnUpdate()
{
}

void Vine::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		if (!grown)
			Grow();
		else
			Retract();
	}
}

void Vine::Grow()
{
	SetTagAlly(TVineG);
	if (grown)
		return;
	grown = true;
	SetHitbox(GetSize().x, GetSize().y * 10);
	SetPosition(GetPosition().x, GetPosition().y - GetSize().y );
}

void Vine::Retract()
{
	SetTagAlly(TVineR);
	if (!grown)
		return;
	grown = false;
	SetHitbox(GetSize().x, GetSize().y);
	SetPosition(GetPosition().x, GetPosition().y + 108);
}