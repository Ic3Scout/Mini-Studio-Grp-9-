#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameManager.h"
#include "AssetManager.h"

class PhysicalEntity;
class Player;

class TestScene : public Scene
{
	Camera mCam;
	AssetManager* assetManager = AssetManager::Get();

	Player* pEntity1;

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
		TAlly,
		TEnemy,
	};

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void UpdateCamera();
	Camera& GetCam() { return mCam; }
};

