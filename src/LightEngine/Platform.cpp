#include "Platform.h"
#include "TestScene.h"
#include "Animation.h"
#include <iostream>

void Platform::OnInitialize()
{
	mKineticBody = false;
	SetTag((int)TestScene::TPlatform);

	SetTexture("Terrain");
	ChangeColor(sf::Color::White);

	LoadAnimation();
}

void Platform::OnUpdate()
{
}

void Platform::OnCollision(Entity* other)
{
	if (other->IsTag(TestScene::TPlatform))
		return;
}

void Platform::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Terrain.json");
}
