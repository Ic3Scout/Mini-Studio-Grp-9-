#include "Platform.h"
#include "TestScene.h"

void Platform::OnInitialize()
{
	SetTag((int)TestScene::TPlatform);
}

void Platform::OnCollision(Entity* other)
{
	if (other->IsTag(TestScene::TPlatform))
		return;
}
