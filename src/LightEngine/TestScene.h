#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GameManager.h"
#include "AssetManager.h"

class PhysicalEntity;
class Player;

class TestScene : public Scene
{
public:
	enum Tag
	{
		TPlayer,
		TPlatform,
		TGun,
		TWeedKiller,
		TWater,
		TAcid,

		Count
	};

	static constexpr int TAG_COUNT = static_cast<int>(Count); 
private:
	Camera mCam;
	AssetManager* assetManager = AssetManager::Get();

	Player* pEntity1;

	PhysicalEntity* pEntitySelected;

	int mTransitions[TAG_COUNT][TAG_COUNT];
private:
	void TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y);
	void InitTransitions();
	void SetTransition(Tag from, Tag to, bool value) { mTransitions[(int)from][(int)to] = value; } 

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void UpdateCamera();
	Camera& GetCam() { return mCam; }

	bool IsAllowedToCollide(int tag1, int tag2);
};

