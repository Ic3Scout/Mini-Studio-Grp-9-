#include "End.h"
#include "TestScene.h"
#include "Player.h"
#include "Camera.h"

void End::OnInitialize()
{
	SetTag(TestScene::TEnd);
	SetIsHitboxActive(false);
	isTriggered = false;
	float mAnimationDuration = 3.f;
	float mProgress = 0.f;
}

void End::OnUpdate()
{
	if (mHitbox.isActive == false)
	{
		SetIsHitboxActive(true);
	}

	if (isTriggered)
	{
		TestScene* pScene = GetScene<TestScene>();

		Player* pCurrentPlayer = pScene->GetPlayer();

		Camera& pCam = pScene->GetCam();

		pCam.SetFocus(false);

		if (pCurrentPlayer->GetPosition().x > pCam.GetView()->getCenter().x + 720)
		{
			std::cout << "Le player est plus la : FIN\n";
			pCurrentPlayer->Destroy();

			isAnimationTriggered = true;
		}

		if (isAnimationTriggered == true)
		{

			if (pCam.GetView()->getCenter().y < -500)
			{
				std::cout << "La cam est a -500 de hauteur\n";
				isAnimationTriggered = false;
			}
			else
				pCam.Move(0, -100 * GetDeltaTime());

		}
		
		pCurrentPlayer->SetSide(1);
		pCurrentPlayer->SetSpeed(250);

	}
}

void End::FixedUpdate(float dt)
{
	GetScene<TestScene>()->UpdateCamera();
}

void End::OnCollision(Entity* pOther)
{
	if(isTriggered)
		return;

	if (pOther->IsTag(TestScene::TPlayer))
	{
		std::cout << "Activated\n";
		isTriggered = true;
	}
}
