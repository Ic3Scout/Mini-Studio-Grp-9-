#include "Ivy.h"
#include "TestScene.h"

Ivy::Ivy() : Enemy(IVY_HP) {}

void Ivy::OnInitialize()
{
	Enemy::OnInitialize();
	SetIsHitboxActive(false);
	SetTagEnemy(TagEnemy::TIvy); 
	mIsDead = false;
}

void Ivy::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TPlayer))
	{
		if (mPlayerInContact == false)
		{
			mPlayerInContact = true;
		}
	}
}

void Ivy::OnUpdate()
{
	Enemy::OnUpdate();

	if (posInitial)
	{
		mInitialPosition = GetPosition().x;
		posInitial = false;
	}
	if (mPlayerInContact == true && posInitial == false)
	{
		HandleAction();
		mCounter += GetDeltaTime();
		if (mCounter >= mTimer)
		{
			mCounter = 0.f;
			mPlayerInContact = false;
		}
	}
	float currentPosition = GetPosition().x;
	float size = GetSize().x;
	float range = 4 * size;

	if (currentPosition >= mInitialPosition + range)
	{
		mDirection = -1;
	}
	else if (currentPosition <= mInitialPosition - range)
	{
		mDirection = 1;
	}

	SetPosition(currentPosition + mDirection * mSpeed * GetDeltaTime(), GetPosition().y);

	if (mIsDead)
	{
		Destroy();
	}
}

void Ivy::HandleAction()
{
	std::cout << "Oof\n";
	player->SetSpeed(parameters->mMaxSpeed/2); 
}