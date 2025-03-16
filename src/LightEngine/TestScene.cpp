#include "TestScene.h"
#include "PhysicalEntity.h"
#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

#include <SFML/Graphics.hpp>

void TestScene::OnInitialize()
{
	int height = GetWindowHeight();
	int width = GetWindowWidth();

	pCam.Resize(width, height);
	pCam.SetFocus(true);

	pEntity1 = CreateEntity<PhysicalEntity>({ 50.f, 150.f }, sf::Color::White);
	pEntity1->SetPosition(width / 2.f, height / 2.f);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsHitboxActive(false);
	
	sf::Texture* texture = assetManager->GetTexture("../../../res/Assets/248259.png");
	pEntity1->GetShape()->setTexture(texture);

	pEntity2 = CreateEntity<PhysicalEntity>({ 50.f,50.f }, sf::Color::Red);
	pEntity2->SetPosition(width / 2.f - 100, height / 2.f);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsHitboxActive(false);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if (pCam.GetFocus())
		{
			pCam.SetFocus(false);
		}
		else
		{
			pCam.SetFocus(true);
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

	if (pCam.GetFocus())
	{
		pCam.SetPosition(pEntity1->GetPosition()); // Pour suivre l'entité 1
	}

	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	UpdateCamera();
}

void TestScene::UpdateCamera()
{
	GameManager::Get()->SetCamera(pCam);
}