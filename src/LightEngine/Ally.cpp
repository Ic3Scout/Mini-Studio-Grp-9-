#include "Ally.h"
#include "TestScene.h"

void Ally::OnInitialize()
{
	SetTag(TestScene::TAlly);
}

bool Ally::IsTagAlly(int tagAlly)
{
	if (mTagAlly == tagAlly)
		return true;

	return false;
}
