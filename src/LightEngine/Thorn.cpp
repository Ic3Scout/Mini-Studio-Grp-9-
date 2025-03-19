#include "Thorn.h"
#include "TestScene.h"

Thorn::Thorn() : Enemy(THORN_HP) {}

void Thorn::OnInitialize()
{
    mKineticBody = false;
    Enemy::OnInitialize();
    SetTagEnemy(TagEnemy::TThorn);
    SetRigidBody(false);
    mIsDead = false;
    mProximityRadius = GetSize().x * 1.5f + GetSize().x / 2 + player->GetSize().x / 2;
	mDelay = 2.f;
	mDelay1 = 2.f;
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
        std::cout << "OOF\n";

        if (mProgress <= 0 && isActive == true)
        {
            isActive = false;
            player->TransitionTo(Player::TakingDamage);
            mProgress = mDelay;
        }
    }
}

void Thorn::OnUpdate()
{
    Enemy::OnUpdate();

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

    float distance = GetDistance(playerPosition, thornPosition);

    return distance <= mProximityRadius;
}