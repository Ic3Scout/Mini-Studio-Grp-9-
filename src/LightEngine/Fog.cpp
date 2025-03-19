#include "Fog.h"
#include "TestScene.h"

void Fog::OnInitialize()
{
	Obstacle::OnInitialize();
	SetTagObstacle(TFog);
	SetHitbox(GetSize().x, GetSize().y);
}