#include "Platform.h"
#include "TestScene.h"

void Platform::OnInitialize()
{
	mKineticBody = false;
	SetTag((int)TestScene::TPlatform);
}

void Platform::OnCollision(Entity* other)
{
	if (other->IsTag(TestScene::TPlatform))
		return;
}
