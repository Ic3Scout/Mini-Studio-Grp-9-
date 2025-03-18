#include "Fongus.h"
#include "TestScene.h"

Fongus::Fongus() : Enemy(FONGUS_HP) {}

void Fongus::OnInitialize()
{
	SetTagEnemy(TagEnemy::TFongusR);
	mIsDead = false;
	mDelay = 1.0f;
	mDelay1 = 2.0f;
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
			player->AddRemoveHP(-1);
			mProgress = mDelay;
		}
	}
}

void Fongus::OnUpdate()
{
	HandleDurationTimer();
	HandleDurationTimer1();
	HandleActions();

	if (mIsDead)
	{
		Destroy();
	}
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
				SetHitbox(GetSize().x * 5, GetSize().y * 5);

				SetTagEnemy(TagEnemy::TFongusG);
				toxic = true;

				mActionTimer = 3.0f;
				mActionState = 1;
				break;

			case 1:
				SetHitbox(GetSize().x, GetSize().y);

				SetTagEnemy(TagEnemy::TFongusR);
				toxic = false;

				mCooldownTimer = 2.0f;//+ActionTimer
				mActionTimer = 3.0f;
				mActionState = 0;
				break;
			}
		}
	}
}