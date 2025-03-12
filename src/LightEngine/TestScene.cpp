#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Debug.h"

void TestScene::OnInitialize()
{
    pEntity1 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
    pEntity1->SetPosition(100, 100);
    pEntity1->SetRigidBody(false);
    pEntity1->SetGravity(true);

    pEntity2 = CreateEntity<Player>(50, sf::Color::Green);
    pEntity2->SetPosition(500, 100);
    pEntity2->SetRigidBody(false);
    pEntity2->SetGravity(false);

    pEntity3 = CreateEntity<Player>(50, sf::Color::Cyan);
    pEntity3->SetPosition(640, 360);
    pEntity3->SetRigidBody(false);
    pEntity3->SetGravity(true);

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
        TrySetSelectedEntity(pEntity3, event.mouseButton.x, event.mouseButton.y);
    }

    if (event.mouseButton.button == sf::Mouse::Button::Left)
    {
        if (pEntitySelected != nullptr)
        {
            pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
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
    if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }

	Debug::DrawRectangle(400, 600, 500, 50, sf::Color::White);

    pEntity1->Fall(GetDeltaTime());
    pEntity2->Fall(GetDeltaTime());
    pEntity3->Fall(GetDeltaTime());
}