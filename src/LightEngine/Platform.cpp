#include "Platform.h"
#include "TestScene.h"
#include "Animation.h"
#include <iostream>

void Platform::OnInitialize()
{
	PhysicalEntity::OnInitialize();
	mKineticBody = false;
	SetTag((int)TestScene::TPlatform);

	sf::Texture* texture = GetScene<TestScene>()->GetAssetManager()->GetTexture("Terrain");
	GetShape()->setTexture(texture);
	ChangeColor(sf::Color::White);

	LoadAnimation();
}

void Platform::OnUpdate()
{
	PhysicalEntity::OnUpdate();
}

void Platform::OnCollision(Entity* other)
{
	if (other->IsTag(TestScene::TPlatform))
		return;
}

void Platform::LoadAnimation()
{
	SetTexture("Terrain");
	mAnimations->LoadJsonData("../../../res/Assets/Terrain.json");
}
