#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

void TestScene::OnInitialize()
{
	int height = GetWindowHeight();
	int width = GetWindowWidth();

	pCam.Resize(width, height);

	pEntity1 = CreateEntity<Player>(50, sf::Color::Cyan);
	pEntity1->SetPosition(width / 2, height / 2);
	pEntity1->SetRigidBody(false);
  
	pEntity1->SetHitbox(100, 100);
	pEntity1->SetGravity(true);

	pEntity2 = CreateEntity<PhysicalEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(width / 2 - 400, height / 2);

	pEntity2->SetRigidBody(false);
	pEntity2->SetHitbox(100, 100);
	pEntity2->SetIsHitboxActive(false);
	pEntity2->SetGravity(false);

	pPlatforme1 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme1->SetPosition(width / 2, height / 2 + 300);
	pPlatforme1->SetRigidBody(false);
	pPlatforme1->SetHitbox(500, 30);

	pPlatforme2 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme2->SetPosition(width / 2 + 375, height / 2 + 260);
	pPlatforme2->SetRigidBody(false);
	pPlatforme2->SetHitbox(30, 30);

	pPlatforme3 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme3->SetPosition(width / 2 + 750, height / 2 + 200);
	pPlatforme3->SetRigidBody(false);
	pPlatforme3->SetHitbox(30, 30);

	pPlatforme4 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme4->SetPosition(width / 2 - 375, height / 2 + 225);
	pPlatforme4->SetRigidBody(false);
	pPlatforme4->SetHitbox(30, 30);

	pPlatforme5 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme5->SetPosition(width / 2 - 65, height / 2 + 70);
	pPlatforme5->SetRigidBody(false);
	pPlatforme5->SetHitbox(30, 30);

	pPlatforme5 = CreateEntity<PhysicalEntity>(15, sf::Color::Red);
	pPlatforme5->SetPosition(width / 2 - 65, height / 2 + 170);
	pPlatforme5->SetRigidBody(false);
	pPlatforme5->SetHitbox(30, 30);



	pEntitySelected = nullptr;
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
		TrySetSelectedEntity(pEntity2, mousePos.x, mousePos.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(mousePos.x, mousePos.y, 200.f);
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

	pCam.SetPosition(pEntity1->GetPosition()); // Pour suivre l'entit� 1

	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	pEntity1->Fall(GetDeltaTime());
	pEntity2->Fall(GetDeltaTime());

	UpdateCamera();
}

void TestScene::UpdateCamera()
{
	GameManager::Get()->SetCamera(pCam);
}