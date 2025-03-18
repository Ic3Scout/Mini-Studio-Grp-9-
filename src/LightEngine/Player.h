#pragma once
#include "PhysicalEntity.h"
#include "Water.h"
#include <vector>
#include <iostream>
#include "Health.h"
#include "Character.h"


#define PLAYER_HP 4

class PlayerUI;
class AmmoBar;
class Weapon;
class PlayerAction;

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mDeceleration = 125.f;

	float mMaxSpeed = 250.f;
	float mAcceleration = 670.f;

	float mDashReloadTime = 5.f;
};

class Player : public Character
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
	State mState = Idle;

	PlayerParameter mParameters;

	std::vector<PlayerUI*> mUI;

	std::vector<Weapon*> mWeapons;

	float mDelayToSwap = 1.f;

	int mSide = 1; //Right : Left = -1

	float mJoyX;

	bool mIsMoving = false;

	float mProgressDashReload = 0.f;

	int mTransitions[STATE_COUNT][STATE_COUNT];
	PlayerAction* mAction[STATE_COUNT];

	void SetTransition(State from, State to, bool value) { mTransitions[(int)from][(int)to] = value; }
public:
	Player();

	void BasicControls();

	void InitStates();
	bool TransitionTo(State newState);
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
	void OnDestroy() override;
	void FixedUpdate(float dt) override;

	void SwapManager();
	void SwapWeapon();

	Weapon* GetCurrentEquipedWeapon();
	std::vector<Weapon*> GetAllWeapons() { return mWeapons; }

	int GetSide() { return mSide; }

	friend class PlayerAction;
	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Jumping;
	friend class PlayerAction_Falling;
	friend class PlayerAction_TakingDamage;
	friend class PlayerAction_Dying;
	friend class PlayerAction_Dashing;
};
