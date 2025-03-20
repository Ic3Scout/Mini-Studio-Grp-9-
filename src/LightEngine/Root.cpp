#include "Root.h"
#include "TestScene.h"

void Root::OnInitialize()
{
	SetKineticBody(false);
	Obstacle::OnInitialize();
	SetTagObstacle(TagObstacle::TRootR);
	SetHitbox(GetSize().x, GetSize().y);
	SetRigidBody(false);
	mInitialSizeY = GetSize().y;
}

void Root::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(TestScene::TPlayer) && dangerous)
	{
		isActive = true;
	}
}

void Root::OnUpdate()
{
	if (isActive)
	{
		mProgress += GetDeltaTime();
		if (canDealDamage)
		{
			player->TransitionTo(Player::TakingDamage);
			canDealDamage = false;
		}
		else
		{
			if (mProgress >= mDelay)
			{
				isActive = false;
				canDealDamage = true;
				mProgress = 0.f;
			}
		}
	}

	if (mCooldownTimer > 0.f)
	{
		mCooldownTimer -= GetDeltaTime();
	}
	else
	{
		mActionTimer -= GetDeltaTime();
		if (mActionTimer <= 0.f)
		{
			switch (mActionState)
			{
			case 0:
				mShape.setSize({ GetSize().x, GetSize().y * 3 });
				SetPosition(GetPosition().x, GetPosition().y - mInitialSizeY * 2);
				SetHitbox(GetSize().x, GetSize().y);

				SetTagObstacle(TagObstacle::TRootG);
				SetRigidBody(true);
				dangerous = true;

				mActionTimer = 3.f;
				mActionState = 1;
				break;

			case 1:
				mShape.setSize({ GetSize().x, mInitialSizeY });
				SetPosition(GetPosition().x, GetPosition().y + mInitialSizeY * 2);
				SetHitbox(GetSize().x, GetSize().y);

				SetTagObstacle(TagObstacle::TRootR);
				SetRigidBody(false);
				dangerous = false;

				mCooldownTimer = 2.f;//+ActionTimer
				mActionTimer = 3.f;
				mActionState = 0;
				break;
			}
		}
	}
}