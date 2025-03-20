#pragma once
#include "Character.h"
#include "Player.h"

class Player;

class Enemy : public Character
{
public:
	enum TagEnemy
	{
		TThorn,
		TBramble,
		TFongusG,
		TFongusR,
		TIvy,
	};

	Player* player;
	PlayerParameter* parameters;

	int mTagEnemy = -1;

	float mDelay = 0.f;
	float mProgress = 0.f;
	bool isActive = false;

	float mDelay1 = 0.f;
	float mProgress1 = 0.f;
	bool isActive1 = false;

	Enemy(int maxHP);
	
	virtual void OnInitialize();
	virtual void OnUpdate(); 

	void SetTagEnemy(int tagEnemy) { mTagEnemy = tagEnemy; }

	bool IsTagEnemy(int tagEnemy) const { return mTagEnemy == tagEnemy; }

	void HandleDurationTimer();

	void HandleDurationTimer1();
};


