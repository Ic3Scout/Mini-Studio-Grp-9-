#include "Bridge.h"
#include "TestScene.h"
#include <iostream>

void Bridge::OnInitialize()
{
	SetRigidBody(true);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TBridge);
	SetHitbox(GetSize().x, GetSize().y);
	mInitialSizeX = GetSize().x;
	mSizeX = GetSize().x;
}

void Bridge::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TWater))
	{
		mGrowing = true;
	}
}

void Bridge::OnUpdate()
{
	if (mGrowing)
	{
		if (mProgress <= mDuration)
			mProgress += GetDeltaTime();

		if (mProgress >= mDuration)
		{
			Grow();
			mProgress = 0.0f;
		}
	}
	if (mGrowProgress >= mGrowDistance)
	{
		mGrowing = false;
		mGrowDistance = 0;
	}
}

void Bridge::Grow()
{
	mSizeX += mInitialSizeX;
	mShape.setSize({ mSizeX, GetSize().y });
	SetPosition(GetPosition().x - mInitialSizeX, GetPosition().y);

	SetHitbox(GetSize().x, GetSize().y);
	mGrowProgress++;
	GetScene<TestScene>()->GetAssetManager()->GetSound("Transition")->play();
}