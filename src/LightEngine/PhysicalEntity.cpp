#include "PhysicalEntity.h"
#include "Utils.h"

void PhysicalEntity::ToggleGravity(bool b)
{
	mGravity = b;
}

void PhysicalEntity::SetGravityIntensity(float f)
{
	mGravityIntensity = f;
}

void PhysicalEntity::SetMass(float f)
{
	mMass = f;
}

void PhysicalEntity::SetXDrag(float f)
{
	mXDrag = Utils::Clamp(f, 1.f, 0.f);
}

void PhysicalEntity::SetYDrag(float f)
{
	mYDrag = Utils::Clamp(f, 1.f, 0.f);
}

float PhysicalEntity::GetMass()
{
	return mMass;
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

void PhysicalEntity::AddForce(sf::Vector2f dir, float intensity, Force type)
{
	mForces.push_back({ dir * intensity, type });
}

void PhysicalEntity::FixedUpdate(float dt)
{
	sf::Vector2f velocity = mDirection * mSpeed;

	if (mGravity)
	{
		AddForce(sf::Vector2f(0.f, 1.f), mGravityIntensity * mMass, Force::Force);
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
			sf::Vector2f acceleration = forceVelocity / mMass;
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

	mPrevVelocity = mDirection * mSpeed;

	mForces.clear();
	mSpeed = Utils::GetMagnitude(velocity);
	Utils::Normalize(velocity);
	mDirection = velocity;

	Entity::FixedUpdate(dt);
}



