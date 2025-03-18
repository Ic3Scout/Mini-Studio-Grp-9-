#pragma once
#include "Entity.h"
#define GRAVITY_ACCELERATION 981.f

class PhysicalEntity : public Entity
{
public:
    enum class Force
    {
        Impulse,
        Force,
    };
private:
    bool mGravity = false;

    float mMaxXVelocity = 1500.f;
    float mMaxYVelocity = 1500.f;
    float mMinXVelocity = 0.f;
    float mMinYVelocity = 0.f;
    float mXDrag = 0.f;
    float mYDrag = 0.f;

    sf::Vector2f mPrevVelocity = sf::Vector2f(0.f, 0.f);

    std::vector<std::pair< sf::Vector2f, Force >> mForces;

public:
    void ToggleGravity(bool b);
    void SetXDrag(float f);
    void SetYDrag(float f);
    void ResetYForce();
    void ResetXForce();
    void SetMinVelocity(float x = 0.f, float y = 0.f);
    void SetMaxVelocity(float x = 1500.f, float y = 1500.f);

    sf::Vector2f GetVelocity();

    void AddForce(sf::Vector2f dir, float intensity, Force type);
    void FixedUpdate(float dt) override;
};