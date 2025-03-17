#include "Animation.h"
#include <iostream>
#include <fstream>

void Animation::LoadJsonData(const char* path)
{
	// Lire le fichier JSON
	std::ifstream inputFile(path);

	if (!inputFile.is_open()) 
	{
		std::cerr << "Erreur lors de l'ouverture du fichier JSON." << std::endl;
		return;
	}

	inputFile >> data;
	inputFile.close();
}

void Animation::LoadAnimationSingle(const char* name)
{
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["animations"][name]["frames"];
	int frameIndex = FindIndex(name);

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i, (0 + frameSize.y * frameIndex) };
		sf::IntRect frame = sf::IntRect(framePosition, frameSize );

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = true;

	std::cout << "Animation chargée avec succès" << " (" << mMaxFrame + 1 << " frames)" << std::endl;
}

void Animation::LoadAnimationByRow(const char* name)
{
}

void Animation::LoadAnimationGrid(const char* name)
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

int Animation::FindIndex(const char* name)
{
	int index = 0;

	for (auto it = data["animations"].begin(); it != data["animations"].end(); ++it, ++index) 
	{
		if (it.key() == name) 
		{
			std::cout << "Position de" << name << " : " << index << std::endl;
			return index;
		}
	}
	std::cout << name << " n'existe pas dans le JSON." << std::endl;
	return -1;
}

