#include "Enemy.h"
#include "TestScene.h"

Enemy::Enemy(int maxHP) : Character(maxHP)
{
	player = GetScene<TestScene>()->GetPlayer();
	parameters = player->GetParameters();
}

void Enemy::OnInitialize()
{
	PhysicalEntity::OnInitialize();
	SetTag(TestScene::TEnemy);
}

void Enemy::OnUpdate()
{
	PhysicalEntity::OnUpdate();
}

void Enemy::HandleDurationTimer()
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
}

void Enemy::HandleDurationTimer1()
{
	if (isActive1 == false)
	{
		mProgress1 -= GetDeltaTime();

		if (mProgress1 < 0)
		{
			isActive1 = true;
			mProgress1 = 0.f;
		}
	}
}