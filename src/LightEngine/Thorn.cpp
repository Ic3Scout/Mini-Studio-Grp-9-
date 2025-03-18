#include "Thorn.h"
#include "TestScene.h"

Thorn::Thorn() : Enemy(THORN_HP) {}

void Thorn::OnInitialize()
{
    SetTagEnemy(TagEnemy::TThorn);
    mIsDead = false;
    mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;
	mDelay = 2.0f;
	mDelay1 = 2.0f;
}

void Thorn::OnCollision(Entity* collidedWith)
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
        if (mProgress <= 0 && isActive == true)
        {
            isActive = false;
            player->AddRemoveHP(-1);
            mProgress = mDelay;
        }
    }
}

void Thorn::OnUpdate()
{
    HandleDurationTimer();
    HandleDurationTimer1();

    if (mCooldownTimer > 0.0f)
    {
        mCooldownTimer -= GetDeltaTime();
    }

    else if (IsPlayerInProximity())
    {
        if (!mActionTriggered)
        {
            SetHitbox(GetSize().x * 3, GetSize().y);

            mActionTimer = 1.0f;
            mActionTriggered = true;
        }
    }

    if (mActionTriggered)
    {
        mActionTimer -= GetDeltaTime();
        if (mActionTimer <= 0.0f)
        {
            SetHitbox(GetSize().x, GetSize().y);

            mActionTriggered = false;
            mCooldownTimer = 3.0f;
        }
    }

    if (mIsDead)
    {
        Destroy();
    }
}

bool Thorn::IsPlayerInProximity()
{
    sf::Vector2f playerPosition = player->GetPosition();
    sf::Vector2f thornPosition = GetPosition();

    float distance = std::sqrt(std::pow(playerPosition.x - thornPosition.x, 2) + std::pow(playerPosition.y - thornPosition.y, 2));

    return distance <= mProximityRadius;
}