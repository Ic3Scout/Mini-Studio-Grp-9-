#include "TestScene.h"
#include "PhysicalEntity.h"
#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

void TestScene::OnInitialize()
{
	int height = GetWindowHeight();
	int width = GetWindowWidth();

	pCam.Resize(width, height);

	pEntity1 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
	pEntity1->SetPosition(width / 2, height / 2);
	pEntity1->SetRigidBody(false);

	pEntity2 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
	pEntity2->SetPosition(-500, height / 2);
	pEntity2->SetRigidBody(false);

	pEntitySelected = nullptr;
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			sf::RenderWindow* win = GameManager::Get()->GetWindow();
			sf::Vector2f mousePos = win->mapPixelToCoords(sf::Mouse::getPosition(*win));
			pEntitySelected->GoToPosition(mousePos.x, mousePos.y, 200.f);
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

	pCam.SetPosition(pEntity1->GetPosition()); // Pour suivre l'entité 1

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