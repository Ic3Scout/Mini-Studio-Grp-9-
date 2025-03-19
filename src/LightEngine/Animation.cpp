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
	mCurrentAnimation = name;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["animations"][name]["frames"];
	int frameIndex = data["animations"][name]["index"];
	int spaceIBT = data["frame_size"]["space"];

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i + spaceIBT, (frameSize.y * frameIndex) + 1 * frameIndex };
		sf::IntRect frame = sf::IntRect(framePosition, frameSize );

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = data["animations"][name]["loop"];
}

void Animation::LoadAnimationByRow(const char* eltName)
{
	mCurrentAnimation = eltName;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };

	int frameCount = data["elements"][eltName]["frames"];
	int frameIndex = FindIndexE(eltName);

	for (int i = 0; i < frameCount; i++)
	{
		sf::Vector2i framePosition = { frameSize.x * i, frameSize.y * frameIndex };
		sf::IntRect frame = sf::IntRect(framePosition, frameSize);

		mTextureRects.push_back(frame);
	}

	mMaxFrame = mTextureRects.size() - 1;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = false;
}

void Animation::LoadAnimationGrid(const char* name)
{
	mCurrentAnimation = name;
	mTextureRects.clear();

	sf::Vector2i frameSize = { data["frame_size"]["width"], data["frame_size"]["height"] };
	sf::Vector2i frameIndex = { data["elements"][name]["x"], data["elements"][name]["y"]}; 

	sf::Vector2i framePosition = { (frameSize.x + 1) * frameIndex.x, (frameSize.y + 1) * frameIndex.y };
	sf::IntRect frame = sf::IntRect(framePosition, frameSize);

	mTextureRects.push_back(frame);

	mMaxFrame = 0;
	mCurrentFrame = 0;
	mElapsedTime = 0.f;
	mLoop = false;
	mStatic = true;
}

void Animation::Update(float dt)
{
	if (mMaxFrame <= 0 || mStatic == true)
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

const char* Animation::GetCurrentAnimation()
{
	return mCurrentAnimation;
}

int Animation::GetMaxFrame()
{
	return mMaxFrame;
}

int Animation::GetCurrentFrameIndex()
{
	return mCurrentFrame;
}

sf::IntRect* Animation::GetCurrentFrame()
{
	if (mMaxFrame <= 0 && mStatic == false) 
		return nullptr;

	return &mTextureRects[mCurrentFrame];
}

int Animation::FindIndexA(const char* name)
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

int Animation::FindIndexE(const char* name)
{
	int index = 0;

	for (auto it = data["elements"].begin(); it != data["elements"].end(); ++it, ++index)
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


