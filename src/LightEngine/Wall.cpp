#include "Wall.h"
#include "TestScene.h"

void Wall::OnInitialize()
{
	Obstacle::OnInitialize();
	SetTagObstacle(TWall);
	SetHitbox(GetSize().x, GetSize().y);
}