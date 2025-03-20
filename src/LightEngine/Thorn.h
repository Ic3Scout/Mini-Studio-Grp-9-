#pragma once
#include "Enemy.h"


#define THORN_HP 1

class Thorn : public Enemy
{
    float mProximityRadius = 0.f;
    float mActionTimer = 0.f;
    bool mActionTriggered = false;
    float mCooldownTimer = 0.f;

public:
    Thorn();

    void OnInitialize() override;
    void OnCollision(Entity* collidedWith) override;

    void FixedUpdate(float dt) override;
    void OnUpdate() override;

    void LoadAnimation() override;

    bool IsPlayerInProximity();
};