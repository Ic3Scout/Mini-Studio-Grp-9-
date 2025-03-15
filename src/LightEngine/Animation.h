#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

class Animation
{
	std::vector<sf::IntRect> mTextureRects;

	int mMaxFrame = 0;
	int mCurrentFrame = 0;
	float mDuration = 100.f;
	float mElapsedTime = 0.f;
	bool mLoop;

public:
	void LoadAnimationSingle(const char* name, json data);
	void LoadAnimationByRow(const char* name, json data);
	void LoadAnimationGrid(const char* name, json data);
	void Update(float dt);

	void SetLoop(bool value) { mLoop = value; }

	sf::IntRect* GetCurrentFrame();
};

