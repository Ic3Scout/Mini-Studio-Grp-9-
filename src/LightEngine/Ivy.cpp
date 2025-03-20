#include "Ivy.h"
#include "TestScene.h"
#include "Animation.h"

Ivy::Ivy() : Enemy(IVY_HP) {}

void Ivy::OnInitialize()
{
	Enemy::OnInitialize();
	SetIsHitboxActive(false);
	SetTagEnemy(TagEnemy::TIvy); 
	mIsDead = false;

	mAnimations = new Animation();
	LoadAnimation();
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

void Ivy::FixedUpadat(float dt)
{
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
			ChangeAnimation("Emerge", "single");
			parameters->mMaxSpeed = parameters->mDefaultMaxSpeed;
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

void Ivy::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Ivy.json");
	SetTexture("Ivy");
	mAnimations->LoadAnimationSingle("Idle");
}

void Ivy::HandleAction()
{
	parameters->mMaxSpeed = parameters->mDefaultMaxSpeed / 2;
}