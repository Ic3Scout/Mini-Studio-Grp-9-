#include "Nenuphloat.h"
#include "TestScene.h"
#include <chrono>

void Nenuphloat::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TNenuphloatR);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Nenuphloat::OnUpdate()
{
	if (grown && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - growTime).count() >= 5)
	{
		Retract();
	}
}

void Nenuphloat::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		Grow();
	}
}

void Nenuphloat::Grow()
{
	SetTagAlly(TNenuphloatG);
	if (!grown)
	{
		grown = true;
		SetHitbox(GetSize().x * 5, GetSize().y);
	}
	growTime = std::chrono::steady_clock::now();
}

void Nenuphloat::Retract()
{
	SetTagAlly(TNenuphloatR);
	if (!grown)
		return;
	grown = false;
	SetHitbox(GetSize().x, GetSize().y);
}