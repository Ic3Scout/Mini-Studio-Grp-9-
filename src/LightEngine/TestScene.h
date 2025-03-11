#pragma once

#include "Scene.h"

class PhysicalEntity;
class Player;

class TestScene : public Scene
{
	PhysicalEntity* pEntity1;
	PhysicalEntity* pEntity2;

	Player* pEntity3;

	PhysicalEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};