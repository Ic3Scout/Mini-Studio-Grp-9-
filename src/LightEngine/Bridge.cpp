#include "Bridge.h"
#include "TestScene.h"

void Bridge::OnInitialize()
{
	Obstacle::OnInitialize();
	SetTagObstacle(TBridge);
	SetHitbox(GetSize().x, GetSize().y);
}