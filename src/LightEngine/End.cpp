#include "End.h"
#include "TestScene.h"
#include "Player.h"
#include "Camera.h"
#include "Animation.h"

void End::OnInitialize()
{
	mScrollSpeed = 1.f;
	SetTag(TestScene::TEnd);
	SetIsHitboxActive(false);
	isTriggered = false;
	mAnimationDuration = 3.f;
	mProgress = 0.f;
	mDelayBeforeAnimation = 3.f;
	mProgressDelay = 0.f;
	mProgressToDestroyPlayer = 0.f;
	pOwner = GetScene<TestScene>()->GetPlayer();
	mEndTheGame = false;
	mEndTimer = 6.f;

	mAnimations->LoadJsonData("../../../res/Assets/Json/Station.json");
	SetTexture("Station");
	mAnimations->LoadAnimationSingle("Idle");
}

void End::OnUpdate()
{
	if (mAnimations->IsFinished())
	{
		ChangeAnimation("Idle", "single");
	}

	if (mHitbox.isActive == false)
	{
		SetIsHitboxActive(true);
	}

	if (isTriggered)
	{
		TestScene* pScene = GetScene<TestScene>();

		Camera& pCam = pScene->GetCam();

		pCam.SetFocus(false);


		if (isAnimationTriggered == true)
		{
			if (pCam.GetView()->getCenter().y < -1000)
			{
				isAnimationTriggered = false;
				GetScene<TestScene>()->GetAssetManager()->GetSound("Suspense")->stop();
				GetScene<TestScene>()->GetAssetManager()->GetSound("Revelation")->play();
				mEndTheGame = true;
			}
			else
			{
				mScrollSpeed += mScrollSpeed * 1.1 * GetDeltaTime();

				pCam.Move(0, -10 * mScrollSpeed * GetDeltaTime());
			}
		}


		if (pOwner != nullptr)
		{
			if(mProgressDelay <= mDelayBeforeAnimation)
				mProgressDelay += GetDeltaTime();

			sf::Vector2f playerPos = pOwner->GetPosition();
			sf::Vector2f pos = GetPosition();

			std::cout << playerPos.x << "/" << pos.x << std::endl;
			
			bool isPlayerArrived = playerPos.x >= pos.x;

			if (isPlayerArrived)//|| mProgressDelay >= mDelayBeforeAnimation)
			{
				pOwner->SetDirection(0, GetDirection().y);
				pOwner->SetSpeed(0);

				if (mProgressToDestroyPlayer >= 0.69f)
				{
					pOwner->Destroy();
					pOwner = nullptr;

					isAnimationTriggered = true;
					GetScene<TestScene>()->GetAssetManager()->GetSound("Suspense")->play();
					GetScene<TestScene>()->GetAssetManager()->GetMusic("MainMusic")->stop();
				}
				else
					mProgressToDestroyPlayer += GetDeltaTime();
			
			}

			if (pOwner != nullptr && isPlayerArrived == false)
			{
				pOwner->TransitionTo(Player::AFK);
				pOwner->SetGravity(true);
				pOwner->SetDirection(1, GetDirection().y);
				pOwner->SetSpeed(75);
			}
		}

		

		if (mEndTheGame)
		{
			mEndTimer -= GetDeltaTime();

			if (mEndTimer < 0)
			{
				std::cout << "This is The End of the Demo !\n";
				exit(666);
			}
		}
	}
}

void End::FixedUpdate(float dt)
{
	GetScene<TestScene>()->UpdateCamera();
}

void End::OnCollision(Entity* pOther)
{
	if (isTriggered)
		return;

	if (pOther->IsTag(TestScene::TPlayer))
	{
		std::cout << "Activated\n";
		isTriggered = true;

		ChangeAnimation("Used", "single"); 
	}
}
