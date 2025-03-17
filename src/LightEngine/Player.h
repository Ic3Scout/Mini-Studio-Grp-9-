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
class Station;

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mDeceleration = 125.f;

	float mMaxSpeed = 250.f;
	float mAcceleration = 670.f;

	int respawnX = 640.f;
	int respawnY = 380.f;
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

	int mTransitions[STATE_COUNT][STATE_COUNT];

	void SetTransition(State from, State to, bool value) { mTransitions[(int)from][(int)to] = value; }
public:
	Player();

	void BasicControls();

	void InitStates();

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump();
	void Respawn(int x, int y);
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
	void OnDestroy() override;

	void SwapManager();
	void SwapWeapon();

	Weapon* GetCurrentEquipedWeapon();
	std::vector<Weapon*> GetAllWeapons() { return mWeapons; }

	int GetSide() { return mSide; }
};
