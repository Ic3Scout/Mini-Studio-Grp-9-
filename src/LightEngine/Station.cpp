#include "Station.h"

void Station::OnInitialize()
{
	Ally::OnInitialize();
	SetTagAlly(TStation);
	SetRigidBody(false);
	SetHitbox(GetSize().x, GetSize().y);
}

void Station::OnUpdate()
{
	Ally::OnUpdate();
}
