#pragma once
#include "Character.h"

class Player;

class Enemy : public Character
{
public:
	enum TagEnemy
	{
		TThorn,
		TBramble,
		TFongus,
		TIvy,
	};

	Player* player;

	int mTagEnemy = -1;

	Enemy(int maxHP);
	
	virtual void OnInitialize() ;

	void SetTagEnemy(int tagEnemy) { mTagEnemy = tagEnemy; }

	bool IsTagEnemy(int tagEnemy) const { return mTagEnemy == tagEnemy; }
};


