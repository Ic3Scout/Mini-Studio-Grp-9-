#pragma once
#include "Ally.h"

class Nenuphloat : public Ally
{
    float mDuration = 5.f;
    float mProgress = 0.f;
public:
    void OnInitialize() override;
    void OnUpdate() override;
    void OnCollision(Entity* collidedWith) override;

private:
    void Grow();
    void Retract();
    bool grown = false;
};