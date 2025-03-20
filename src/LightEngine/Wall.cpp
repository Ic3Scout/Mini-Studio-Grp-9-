#include "Wall.h"
#include "TestScene.h"

void Wall::OnInitialize()
{
	SetRigidBody(true);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TWall);
	SetHitbox(GetSize().x, GetSize().y);

}

void Wall::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		mIsActive = true;
	}
}

void Wall::OnUpdate()
{
	if(mIsActive)
	{
		mProgress += GetDeltaTime();
	}

	if (mProgress >= mDelay)
	{
		mIsActive = false;
		mProgress = 0.f;
		mHP--;
	}

	if (mHP <= 0)
	{
		GetScene<TestScene>()->GetAssetManager()->GetSound("DeadMonster")->play();
		Destroy();
	}
}