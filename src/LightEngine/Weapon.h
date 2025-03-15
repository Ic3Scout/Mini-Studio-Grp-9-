#pragma once
#include "Entity.h"

class Player;

class Weapon : public Entity
{
protected:
	Player* pOwner;

	int mPlayerSide;

	int mMaxAmmos;
	int mAmmos;
	float mReloadTime;
	float mProgressReload = 0.f;

	float mDelayBeforeReloading;
	float mProgressDelay = 0.f;

	float mShootingDelay;

	bool mIsEquiped = false;

	void AddRemoveAmmo(int value);
public:
	virtual void OnUpdate() = 0;
	virtual void SetOwner(Player* pOwner) { this->pOwner = pOwner; }
	virtual void Shoot() = 0;

	void ReloadManager();
	void ShootManager(sf::Keyboard::Key key, int valueJoystick1, int valueJoystick2);
	void ShootManager(sf::Mouse::Button mouseButton, int valueJoystick1, int valueJoystick2);

	float GetRatioMunition() { return (float) mAmmos / (float) mMaxAmmos; }

	bool GetIsEquiped() { return mIsEquiped; }
	void SetIsEquiped(bool value) { mIsEquiped = value; }

	Player* GetOwner() {return pOwner; }
};

