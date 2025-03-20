#include "Fongus.h"
#include "TestScene.h"
#include "Animation.h"
#include "FongusCloud.h"

Fongus::Fongus() : Enemy(FONGUS_HP) {}

void Fongus::OnInitialize()
{
	mKineticBody = false;
	Enemy::OnInitialize(); 
	SetTagEnemy(TagEnemy::TFongusR);
	SetRigidBody(true);
	mIsDead = false;
	mDelay = 1.f;
	mDelay1 = 2.f;

	mCloud = CreateEntity<FongusCloud>({ GetSize().x * 5, GetSize().y * 5 }, sf::Color::Red);

	LoadAnimation();
}

void Fongus::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TAcid))
	{
		if (mProgress1 <= 0 && isActive1 == true)
		{
			isActive1 = false;
			AddRemoveHP(-1);
			mProgress1 = mDelay1;
		}
	}

	if (collidedWith->IsTag(TestScene::TPlayer))
	{
		if (mProgress <= 0 && isActive == true && toxic == true)
		{
			isActive = false;
			player->TransitionTo(Player::TakingDamage);
			mProgress = mDelay;
		}
	}
}

void Fongus::OnUpdate()
{
	Enemy::OnUpdate();

	if (mIsDead)
	{
		Destroy();
		return;
	}

	if (mAnimations->IsFinished())
	{
		ChangeAnimation("Idle", "single");
	}

	HandleDurationTimer();
	HandleDurationTimer1();
	HandleActions();
}

void Fongus::LoadAnimation()
{
	mAnimations->LoadJsonData("../../../res/Assets/Json/Fongus.json");
	SetTexture("Fongus");
	mAnimations->LoadAnimationSingle("Idle");
}

void Fongus::HandleActions()
{
	if (mCooldownTimer > 0.0f)
	{
		mCooldownTimer -= GetDeltaTime();
	}
	else
	{
		mActionTimer -= GetDeltaTime();
		if (mActionTimer <= 0.0f)
		{
			switch (mActionState)
			{
			case 0:
				ChangeAnimation("Attack", "single");
				mCloud->ChangeAnimation("FongusCloud", "byRow");
				mCloud->SetPosition(GetPosition().x, GetPosition().y - GetSize().y);

				SetHitbox(GetSize().x * 5, GetSize().y * 5);

				SetTagEnemy(TagEnemy::TFongusG);
				SetRigidBody(false);
				toxic = true;

				mActionTimer = 3.0f;
				mActionState = 1;
				break;

			case 1:
				mCloud->SetPosition(-1000.f, -1000.f);

				SetHitbox(GetSize().x, GetSize().y);

				SetTagEnemy(TagEnemy::TFongusR);
				SetRigidBody(true);
				toxic = false;

				mCooldownTimer = 2.0f;//+ActionTimer
				mActionTimer = 3.0f;
				mActionState = 0;
				break;
			}
		}
	}
}