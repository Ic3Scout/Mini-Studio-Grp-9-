#include "Vine.h"
#include "TestScene.h"

void Vine::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TVine);
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
		Grow();
	}
}

void Vine::Grow()
{
	if (grown)
		return;
	grown = true;
	SetHitbox(GetSize().x, GetSize().y + 216);
	SetPosition(GetPosition().x, GetPosition().y - 108);
}