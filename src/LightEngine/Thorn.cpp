#include "Thorn.h"
#include"TestScene.h"
#include"Player.h"

Thorn::Thorn() : Enemy(THORN_HP) {}

void Thorn::OnInitialize()
{
	SetTagEnemy(TagEnemy::TThorn);
	mMaxHP = 1;
	mIsDead = false;
}

void Thorn::OnCollision(Entity* collidedWith)
{
	//if (collidedWith->IsTag(TestScene::TAcid))
	//{
	//	AddRemoveHP(-1);
	//}

	if (collidedWith->IsTag(TestScene::TPlayer))
	{
		if (mProgress <= 0 && isActive == true)
		{
			isActive = false;
			player->AddRemoveHP(-1); 
			mProgress = mDuration;
		}
	}
}

void Thorn::OnUpdate()
{
	if (isActive == false)
	{
		mProgress -= GetDeltaTime();

		if (mProgress < 0)
		{
			isActive = true;
			mProgress = 0.f;
		}
	}

	if (mIsDead)
	{
		Destroy();
	}

	std::cout << mProgress << std::endl;
}