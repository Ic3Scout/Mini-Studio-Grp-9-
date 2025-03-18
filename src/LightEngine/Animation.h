#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

class Animation
{
	std::vector<sf::IntRect> mTextureRects;
	json data;

	int mMaxFrame = 0;
	int mCurrentFrame = 0;
	float mDuration = 0.5f;
	float mElapsedTime = 0.f;
	bool mLoop;
	bool mStatic = false;

public:
	void SetLoop(bool value) { mLoop = value; }

	void LoadJsonData(const char* path);
	void LoadAnimationSingle(const char* name);
	void LoadAnimationByRow(const char* name);
	void LoadAnimationGrid(const char* name);

	void Update(float dt);

	sf::IntRect* GetCurrentFrame();

private:
	int FindIndexA(const char* name);
	int FindIndexE(const char* eltName);
};

