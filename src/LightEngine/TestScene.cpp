#include "TestScene.h"
#include "Player.h"
#include "Debug.h"

void TestScene::OnInitialize()
{
    pEntity1 = CreateEntity<Player>(100, sf::Color::Red);
    pEntity1->SetPosition(300, 360);
    pEntity1->SetRigidBody(true);

    pEntity2 = CreateEntity<Player>(50, sf::Color::Green);
    pEntity2->SetPosition(980, 360);
    pEntity2->SetRigidBody(true);

    pEntity3 = CreateEntity<Player>(50, sf::Color::Cyan);
    pEntity3->SetPosition(640, 360);
    pEntity3->SetRigidBody(true);

    pEntitySelected = nullptr;

    // Initialiser les états des touches
    mIsMovingRight = false;
    mIsMovingLeft = false;
}

void TestScene::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::D)
        {
            mIsMovingRight = true;
        }
        if (event.key.code == sf::Keyboard::Key::Q)
        {
            mIsMovingLeft = true;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Key::D)
        {
            mIsMovingRight = false;
        }
        if (event.key.code == sf::Keyboard::Key::Q)
        {
            mIsMovingLeft = false;
        }
    }
}

void TestScene::OnUpdate()
{
    if (mIsMovingRight)
    {
        pEntity3->MoveRight(1.f);
    }
    if (mIsMovingLeft)
    {
        pEntity3->MoveLeft(1.f);
    }

    if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }
}
