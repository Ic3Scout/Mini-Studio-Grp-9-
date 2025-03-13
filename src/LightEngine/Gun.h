#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#define PI 3.1415926535



class Player;

class Gun : public Entity
{
	Player* pOwner;

	float mAngle = 0;

	float mDelay = 0.5f;

public:
	void OnUpdate() override;
	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
	void Shoot();
};

