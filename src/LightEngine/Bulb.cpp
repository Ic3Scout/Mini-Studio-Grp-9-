#include "Bulb.h"

void Bulb::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TBulb);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Bulb::OnUpdate()
{
	Ally::OnUpdate();
}
