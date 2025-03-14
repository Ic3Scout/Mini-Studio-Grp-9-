#pragma once
#include "json.hpp"

class Animation
{
	int mCurrentFrame;
	float mDuration;

public:
	Animation();

	void Update(float dt);
};

