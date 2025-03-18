#include "PhysicalEntity.h"
#include <iostream>

#include "Utils.h"

void PhysicalEntity::ToggleGravity(bool b)
{
	mGravity = b;
}

void PhysicalEntity::SetXDrag(float f)
{
	mXDrag = Utils::Clamp(f, 1.f, 0.f);
}

void PhysicalEntity::SetYDrag(float f)
{
	mYDrag = Utils::Clamp(f, 1.f, 0.f);
}


void PhysicalEntity::ResetXForce()
{
	mDirection.x = 0;
}

void PhysicalEntity::ResetYForce()
{
	mDirection.y = 0;
}

void PhysicalEntity::SetMinVelocity(float x, float y)
{
	mMinXVelocity = x;
	mMinYVelocity = y;
}

void PhysicalEntity::SetMaxVelocity(float x, float y)
{
	mMaxXVelocity = x;
	mMaxYVelocity = y;
}

sf::Vector2f PhysicalEntity::GetVelocity()
{
	return mPrevVelocity;
}

void PhysicalEntity::AddForce(sf::Vector2f dir, float intensity, Force type)
{
	mForces.push_back({ dir * intensity, type });
}

void PhysicalEntity::FixedUpdate(float dt)
{
	sf::Vector2f velocity = mDirection * mSpeed;

	if (mGravity)
	{
		AddForce(sf::Vector2f(0.f, 10.f), GRAVITY_ACCELERATION, Force::Force);
	}

	for (std::pair< sf::Vector2f, Force >& force : mForces)
	{
		sf::Vector2f forceVelocity = force.first;
		Force forceType = force.second;

		if (forceType == Force::Impulse)
		{
			velocity += forceVelocity;
		}
		if (forceType == Force::Force)
		{
			sf::Vector2f acceleration = forceVelocity;
			velocity += acceleration * dt;
		}
	}

	//Drag
	velocity.x -= mXDrag * velocity.x * dt;
	velocity.y -= mYDrag * velocity.y * dt;

	//Max and Min velocity
	velocity.x = Utils::Clamp(velocity.x, mMaxXVelocity, -mMaxXVelocity);
	velocity.y = Utils::Clamp(velocity.y, mMaxYVelocity, -mMaxYVelocity);

	if (abs(velocity.x) < mMinXVelocity && abs(velocity.x) < abs(mPrevVelocity.x))
	{
		velocity.x = 0.f;
	}

	if (abs(velocity.y) < mMinYVelocity && abs(velocity.y) < abs(mPrevVelocity.y))
	{
		velocity.y = 0.f;
	}

	mForces.clear();
	mSpeed = Utils::GetMagnitude(velocity);
	Utils::Normalize(velocity);
	mDirection = velocity;

	mPrevVelocity = mDirection * mSpeed;

	Entity::FixedUpdate(dt);
}