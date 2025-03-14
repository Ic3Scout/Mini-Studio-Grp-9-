#include "Animation.h"

Animation::Animation()
{
	mCurrentFrame = 0;
	mDuration = 100.f;
}

void Animation::Update(float dt)
{
	mDuration -= dt;
	if (mDuration <= 0)
	{
		mDuration += 100.f;
		mCurrentFrame = (mCurrentFrame + 1) % 4;
	}
}
