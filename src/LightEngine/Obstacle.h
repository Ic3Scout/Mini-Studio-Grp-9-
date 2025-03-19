#pragma once
#include "PhysicalEntity.h"

class Obstacle : public PhysicalEntity
{
public:
	enum TagObstacle
	{
		TBridge,
		TRoot,
		TFog,
		TWall,
	};
	int mTagObstacle = -1;

	virtual void OnInitialize();

	void SetTagObstacle(int tagObstacle) { mTagObstacle = tagObstacle; }
	bool IsTagObstacle(int tagObstacle) const { return mTagObstacle == tagObstacle; }
};