#include "Animation.h"
#include <iostream>

void Animation::LoadAnimationSingle(const char* name, json data)
{
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["animations"][name]["frames"];

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i, frameSize.y * i};
		sf::IntRect frame = sf::IntRect(framePosition, frameSize);

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = true;

	std::cout << "Animation chargée avec succès" << " (" << mMaxFrame << " frames)" << std::endl;
}

void Animation::LoadAnimationByRow(const char* name, json data)
{
}

void Animation::LoadAnimationGrid(const char* name, json data)
{
}

void Animation::Update(float dt)
{
	if (mMaxFrame <= 0)
		return;

	mElapsedTime += dt;
	if (mElapsedTime >= mDuration) 
	{
		mElapsedTime = 0.f;
		if (mCurrentFrame < mMaxFrame) 
		{
			mCurrentFrame++;
		}
		else if (mLoop) 
		{
			mCurrentFrame = 0; 
		}
	}
}

sf::IntRect* Animation::GetCurrentFrame()
{
	if (mMaxFrame <= 0) 
		return nullptr;

	return &mTextureRects[mCurrentFrame];
}

