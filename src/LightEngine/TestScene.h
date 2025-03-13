#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameManager.h"

class PhysicalEntity;
class Player;

class TestScene : public Scene
{
	Camera pCam;

	Player* pEntity1;
	PhysicalEntity* pEntity2;

	PhysicalEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void UpdateCamera();
};

