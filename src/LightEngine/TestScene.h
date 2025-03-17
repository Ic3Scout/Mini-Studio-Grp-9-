#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameManager.h"

class PhysicalEntity;
class Player;

class TestScene : public Scene
{
	Camera mCam;

	Player* pEntity1;
	PhysicalEntity* pEntity2;
	PhysicalEntity* pPlatforme1;
	PhysicalEntity* pPlatforme2;
	PhysicalEntity* pPlatforme3;
	PhysicalEntity* pPlatforme4;
	PhysicalEntity* pPlatforme5;
	PhysicalEntity* pPlatforme6;

	PhysicalEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y);

public:
	enum Tag
	{
		TPlayer,
		TPlatform,
		TGun,
		TWeedKiller,
		TWater,
		TAcid,
		TEnnemy,
	};

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void UpdateCamera();
	Camera& GetCam() { return mCam; }
};

