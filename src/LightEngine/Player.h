#pragma once
#include "PhysicalEntity.h"
#include "Water.h"
#include <vector>
#include <iostream>

class Weapon;
class WeedKiller;
class Gun;

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mDeceleration = 125.f;

	float mMaxSpeed = 250.f;
	float mAcceleration = 670.f;
};

class Player : public PhysicalEntity
{
public:
	enum State
	{
		Idle,
		Moving,
		Jumping,
		Dashing,
		Falling,
		TakingDamage,
		Dying,

		Count
	};

	static constexpr int STATE_COUNT = static_cast<int>(State::Count); 

private:
	PlayerParameter mParameters;

	std::vector<Weapon*> mWeapons;

	State mState = Idle;

	float mDelayToSwap = 1.f;

	int mSide = 2; //Right

	int mTransitions[STATE_COUNT][STATE_COUNT];

	void SetTransition(State from, State to, bool value) { mTransitions[(int)from][(int)to] = value; }

public:
	Player();

	void BasicControls();

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;

	void SwapManager();
	void SwapWeapon();

	int GetSide() { return mSide; }
};
