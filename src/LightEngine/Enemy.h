#pragma once
#include "Character.h"

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

	int mTagEnemy = -1;

	
	virtual void OnInitialize() ;

	void SetTagEnemy(int tagEnemy) { mTagEnemy = tagEnemy; }

	bool IsTagEnemy(int tagEnemy) const { return mTagEnemy == tagEnemy; }
};


