#pragma once
#include "Obstacle.h"
class Bridge : public Obstacle
{
	bool mGrowing = false;
	float mInitialSizeX = 0.f;
	float mSizeX = 0.f;
	int mGrowDistance = 5;
	int mGrowProgress = 0;

	float mDuration = 0.25f;
	float mProgress = 0.f;
public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

	void LoadAnimation() override;
	void Grow();
};