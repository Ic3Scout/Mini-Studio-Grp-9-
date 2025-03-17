#include "Nenuphloat.h"
#include "TestScene.h"

void Nenuphloat::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TNenuphloatR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Nenuphloat::OnUpdate()
{
}

void Nenuphloat::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		if (!grown)
			Grow();
		else
			Retract();
	}
}

void Nenuphloat::Grow()
{
	SetTagAlly(TNenuphloatG);
	if (grown)
		return;
	grown = true;
	SetHitbox(GetSize().x * 3, GetSize().y);
	SetPosition(GetPosition().x, GetPosition().y - 108);
}

void Nenuphloat::Retract()
{
	SetTagAlly(TNenuphloatR);
	if (!grown)
		return;
	grown = false;
	SetHitbox(GetSize().x, GetSize().y);
	SetPosition(GetPosition().x, GetPosition().y + 108);
}