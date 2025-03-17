#pragma once
#include "Ally.h"
#include <chrono>

class Nenuphloat : public Ally
{
public:
    void OnInitialize() override;
    void OnUpdate() override;
    void OnCollision(Entity* collidedWith) override;

private:
    void Grow();
    void Retract();
    bool grown = false;
    std::chrono::steady_clock::time_point growTime;
};