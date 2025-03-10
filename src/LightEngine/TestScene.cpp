#include "TestScene.h"

#include "Player.h"

#include "Debug.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<Player>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateEntity<Player>(50, sf::Color::Green);
	pEntity2->SetPosition(100, 620);
	pEntity2->SetRigidBody(true);
	
	pEntity3 = CreateEntity<Player>(50, sf::Color::Cyan);
	pEntity3->SetPosition(640, 360);
	pEntity3->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Key::D)
		{
			pEntity3->MoveRight(0.2f);
		}
	}
	if (event.KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Key::Q)
		{
			pEntity3->MoveLeft(1.f);
		}
	}
}

void TestScene::TrySetSelectedEntity(Player* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void TestScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}