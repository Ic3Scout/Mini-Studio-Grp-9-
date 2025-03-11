#include "SampleScene.h"
#include "PhysicalEntity.h"
#include "DummyEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(false);

	pEntity2 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
	pEntity2->SetPosition(500, 100);
	pEntity2->SetRigidBody(false);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
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
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
	
	if (event.type!= sf::Event::EventType::JoystickButtonPressed)
	{
		return;
	}
	if (event.joystickButton.button == sf::Joystick::Axis::X)
	{
		
	}
}

void SampleScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}



void SampleScene::OnUpdate()

{
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	/*pEntity1->Fall(GetDeltaTime());*/
	if (sf::Joystick::isConnected(0))
	{
		//std::cout << "JoyStick Connecte" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0,1))
	{
		std::cout << "X Pressed" << std::endl;
	}
	if (sf::Joystick::isButtonPressed(0, 2))
	{
		std::cout << "O Pressed" << std::endl;
	}
	std::cout << "axe X" << x << std::endl;
	std::cout << "axe Y" << y << std::endl;
}