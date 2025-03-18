#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Platform.h"
#include "DummyEntity.h"
#include "Animation.h"
#include "Debug.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include <filesystem>

void TestScene::OnInitialize()
{
	InitAssets();
	InitTransitions();

	int height = GetWindowHeight();
	int width = GetWindowWidth();

	mCam.Resize(width, height);

	pEntity1 = CreateEntity<Player>({ 50.f, 50.f }, sf::Color::White);
	pEntity1->SetPosition(width / 2.f, 750);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsHitboxActive(true);
	pEntity1->SetGravity(true);
	pEntity1->SetKineticBody(true);

	mCam.SetOwner(pEntity1);
	mCam.SetFocus(true);

	std::string filepath = "../../../res/map.txt";
	std::ifstream inputFile(filepath);

	if (!std::filesystem::exists(filepath)) {
		std::cerr << "Erreur : Le fichier n'existe pas a l'emplacement : " << filepath << std::endl;
	}

	if (!inputFile) {
		std::cerr << "Erreur : Impossible d'ouvrir " << filepath << std::endl;
	}

	std::vector<Platform*> platforms;
	std::vector<std::string> map;

	std::string line;
	while (std::getline(inputFile, line)) {
		map.push_back(line);
	}

	inputFile.close();

	const int BLOCK_SIZE = 50;
	int startX = width / 2 - 250; 
	int startY = height / 2 - 200;

	for (size_t y = 0; y < map.size(); ++y) {
		for (size_t x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == 'X') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE * 2, BLOCK_SIZE }, sf::Color::Red);
				block->GetAnimations()->LoadAnimationGrid("Land2");
				block->SetPosition(startX + x * BLOCK_SIZE * 2, startY + y * BLOCK_SIZE);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE * 2, BLOCK_SIZE);
				platforms.push_back(block);
			}
		}
	}

	pEntitySelected = nullptr;

	assetManager->GetMusic("MainMusic")->play();
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed && event.type != sf::Event::EventType::KeyPressed)
		return;

	sf::RenderWindow* win = GameManager::Get()->GetWindow();
	sf::Vector2f mousePos = win->mapPixelToCoords(sf::Mouse::getPosition(*win));

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, mousePos.x, mousePos.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(mousePos.x, mousePos.y, 200.f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if (mCam.GetFocus())
		{
			mCam.SetFocus(false);
		}
		else
		{
			if (pEntity1 != nullptr)
			{
				if (pEntity1->ToDestroy() == false)
					mCam.SetFocus(true);
			}
		}
	}

	if (pEntitySelected != nullptr)
	{
		if (event.key.code == sf::Keyboard::H)
		{
			if (pEntitySelected->GetHitbox()->isActive)
				pEntitySelected->SetIsHitboxActive(false);
			else
				pEntitySelected->SetIsHitboxActive();
		}
	}
}

void TestScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void TestScene::OnUpdate()
{
	float dt = GetDeltaTime();

	
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	int fpsCounter = (int) (1.f / GetDeltaTime());

	sf::Vector2f camPos = mCam.GetView()->getCenter();

	Debug::DrawText(camPos.x + 500, camPos.y - 340, "FPS : " + std::to_string(fpsCounter), sf::Color::White);
}

void TestScene::UpdateCamera()
{
	GameManager::Get()->SetCamera(mCam);
}

bool TestScene::IsAllowedToCollide(int tag1, int tag2)
{
	return mInteractions[tag1][tag2];
}

void TestScene::InitAssets()
{
	assetManager->LoadTexture("Player", "../../../res/Assets/248259.png");
	assetManager->LoadTexture("Terrain", "../../../res/Assets/SpriteSheet_Terrain.png");
	assetManager->LoadMusic("MainMusic", "../../../res/Assets/music/mainmusic.wav")->setLoop(true);
	assetManager->GetMusic("MainMusic")->setVolume(75);
	assetManager->LoadSound("Waterdrop", "../../../res/Assets/sfx/waterdrop.wav")->setVolume(50);
	assetManager->LoadSound("WeedKiller", "../../../res/Assets/sfx/weedkiller.wav")->setVolume(100);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->LoadSound("Checkpoint", "../../../res/Assets/sfx/checkpoint.wav")->setVolume(75);
	assetManager->LoadSound("ReloadWater", "../../../res/Assets/sfx/reloadwater.wav")->setVolume(15);
	assetManager->LoadSound("PlayerJump", "../../../res/Assets/sfx/jump.wav")->setVolume(75);
	assetManager->LoadSound("PlayerShooting", "../../../res/Assets/sfx/shooting.wav")->setVolume(100);
	assetManager->LoadSound("PlayerDash", "../../../res/Assets/sfx/dash.wav")->setVolume(50);
}

void TestScene::InitTransitions()
{
	for (int i = 0; i < TAG_COUNT; i++)
	{
		for (int j = 0; j < TAG_COUNT; j++)
		{
			mInteractions[i][j] = false;
		}
	}

	SetInteractionWith(TPlayer, TPlatform, true);

	SetInteractionWith(TWater, TPlatform, true); 
}
