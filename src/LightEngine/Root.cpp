#include "Root.h"
#include "TestScene.h"

void Root::OnInitialize()
{
	Obstacle::OnInitialize();
	SetTagObstacle(TRoot);
	SetHitbox(GetSize().x, GetSize().y);
}