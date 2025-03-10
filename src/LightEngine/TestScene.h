#pragma once

#include "Scene.h"

class Player;

class TestScene : public Scene
{
	Player* pEntity1;
	Player* pEntity2;
	Player* pEntity3;

	Player* pEntitySelected;

	bool mIsMovingRight;
	bool mIsMovingLeft;


public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};