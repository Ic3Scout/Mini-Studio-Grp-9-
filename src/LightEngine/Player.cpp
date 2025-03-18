#include "Player.h"
#include "Gun.h"
#include "WeedKiller.h"
#include "Weapon.h"
#include "TestScene.h"
#include "Debug.h"
#include "PlayerAmmoBar.h"
#include "PlayerHealthBar.h"
#include "PlayerUI.h"
#include "PlayerAction.h"
#include "Animation.h"

#include <iostream>

Player::Player() : Character(PLAYER_HP)
{
	PlayerHealthBar* pPlayerHB = new PlayerHealthBar();
	PlayerAmmoBar* pPlayerAB = new PlayerAmmoBar();

	mUI.push_back(pPlayerHB);
	mUI.push_back(pPlayerAB);

	for (PlayerUI* ui : mUI)
	{
		ui->SetOwner(this);
	}
}

void Player::BasicControls()
{
	mJoyX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

	mIsMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || mJoyX > 25)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || mJoyX < -25)
		{
			mIsMoving = false;
			mSide = -1;
		}
		else
		{
			mIsMoving = true;
			mSide = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || mJoyX < -25)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || mJoyX > 25)
		{
			mIsMoving = false;
			mSide = 1;
		}
		else
		{
			mIsMoving = true;
			mSide = -1;
		}
	}

	mDirection.x = mSide;

	if (mIsMoving && mState != Falling)
		TransitionTo(Player::Moving);

	if (mIsMoving == false)
		mSpeed = 0.f;

}

void Player::InitStates()
{
	for (int i = 0; i < STATE_COUNT; i++)
	{
		for (int j = 0; j < STATE_COUNT; j++)
		{
			mTransitions[i][j] = false;
		}
	}

	////Idle, Moving,  Jumping,Dashing, Falling, TakingDmg, Dying
	//{ 0,	  1,	   1,	   1,	    1,		 1,			1 }, // Idle
	//{ 1,    0,       1,	   1,       1,       1,         1 }, // Moving
	//{ 0,    1,       0,	   1,       1,       1,         1 }, // Jumping
	//{ 1,    0,       0,	   0,       0,       0,         0 }, // Dashing
	//{ 1,    1,       0,	   1,       0,       1,         1 }, // Falling
	//{ 1,    0,       0,	   0,       0,       0,         1 }, // TakingDmg
	//{ 0,    0,       0,	   0,       0,       0,         0 }  // Dying

	SetTransition(Idle, Moving, true);
	SetTransition(Idle, Jumping, true);
	SetTransition(Idle, Dashing, true);
	SetTransition(Idle, Falling, true);
	SetTransition(Idle, TakingDamage, true);
	SetTransition(Idle, Dying, true);

	SetTransition(Moving, Idle, true);
	SetTransition(Moving, Jumping, true);
	SetTransition(Moving, Dashing, true);
	SetTransition(Moving, Falling, true);
	SetTransition(Moving, TakingDamage, true);
	SetTransition(Moving, Dying, true);

	SetTransition(Jumping, Dashing, true);
	SetTransition(Jumping, Falling, true);
	SetTransition(Jumping, TakingDamage, true);
	SetTransition(Jumping, Dying, true);

	SetTransition(Dashing, Idle, true);
	SetTransition(Dashing, Falling, true);

	SetTransition(Falling, Idle, true);
	SetTransition(Falling, Moving, true);
	SetTransition(Falling, Dashing, true);
	SetTransition(Falling, TakingDamage, true);
	SetTransition(Falling, Dying, true);

	mAction[Idle] = new PlayerAction_Idle();
	mAction[Moving] = new PlayerAction_Moving();
	mAction[Jumping] = new PlayerAction_Jumping();
	mAction[Falling] = new PlayerAction_Falling();
	mAction[TakingDamage] = new PlayerAction_TakingDamage();
	mAction[Dying] = new PlayerAction_Dying();
	mAction[Dashing] = new PlayerAction_Dashing();

}

bool Player::TransitionTo(State newState)
{
	if (mTransitions[(int)mState][(int)newState])
	{
		mAction[(int)newState]->Start(this);
		mState = newState;

		return true;
	}

	return false;
}

void Player::OnInitialize()
{
	InitStates();

	SetTag((int)TestScene::TPlayer);

	sf::Texture* texture = GetScene<TestScene>()->GetAssetManager()->GetTexture("Player");
	GetShape()->setTexture(texture);

	Weapon* gun = CreateEntity<Gun>({ 20, 20 }, sf::Color::White);
	gun->SetOwner(this);

	Weapon* weedKiller = CreateEntity<WeedKiller>({ 20, 20 }, sf::Color::Yellow);;
	weedKiller->SetOwner(this);

	mWeapons.push_back(gun);
	mWeapons.push_back(weedKiller);
}

void Player::OnUpdate()
{
	mAction[mState]->Update(this, GetDeltaTime());

	if (mIsDead)
	{
		TransitionTo(Player::Dying);
		return;
	}

	BasicControls();


	if (mProgressDashReload <= 0)
	{
		Debug::DrawCircle(GetPosition().x, GetPosition().y, 15, sf::Color::Magenta);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 5))
		{
			TransitionTo(Dashing);
			mProgressDashReload = mParameters.mDashReloadTime;
		}
	}
	else
	{
		mProgressDashReload -= GetDeltaTime();
	}

	SwapManager();

	sf::Vector2f pos = GetPosition();

	for (Weapon* w : mWeapons)
	{
		w->SetPosition(pos.x + mSide * mHitbox.size.x * 0.5f, pos.y);

		if (w->IsTag(GetScene<TestScene>()->TGun) && w->GetIsEquiped() == true)
		{
			sf::Vector2f gunPos = w->GetPosition();
			sf::Vector2f gunDir = w->GetDirection();

			Debug::DrawLine(gunPos.x, gunPos.y, gunPos.x + gunDir.x * 300, gunPos.y + gunDir.y * 300, sf::Color::Red);
		}
	}

	for (PlayerUI* ui : mUI)
	{
		ui->UpdateUI();
	}

	/*if (GetPosition().y > 800)
	{
		AddRemoveHP(-1);
		SetPosition(640, 380);
	}*/
	//std::cout << mGravitySpeed << std::endl;
}

void Player::OnCollision(Entity* other)
{
	if (other->IsTag(TestScene::TWater) || other->IsTag(TestScene::TAcid))
		return;

	switch (mHitbox.face)
	{
	case CollideWith::Bottom:
		mGravitySpeed = 0.f;
		break;

	case CollideWith::Top:
		mGravitySpeed = 0.f;
		break;

	case CollideWith::Left:
		break;

	case CollideWith::Right:
		break;

	case CollideWith::Nothing:
		break;

	default:
		std::cout << "Bug\n";
		break;
	}
}

void Player::OnDestroy()
{
	GetScene<TestScene>()->GetCam().SetOwner(nullptr);

	for (Weapon* w : mWeapons)
	{
		w->SetOwner(nullptr);
		w->Destroy();
	}

	mWeapons.clear();

	for (PlayerUI* ui : mUI)
	{
		delete ui;
		ui = nullptr;
	}

	mUI.clear();
}

void Player::FixedUpdate(float dt)
{
	Entity::FixedUpdate(dt);
	PhysicalEntity::FixedUpdate(dt);
}

void Player::SwapManager()
{
	if (mDelayToSwap >= 0.5f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) || sf::Joystick::isButtonPressed(0, 3))
		{
			SwapWeapon();
		}
	}
	else
	{
		mDelayToSwap += GetDeltaTime();
	}
}

void Player::SwapWeapon()
{
	mDelayToSwap = 0.f;

	auto it = mWeapons.begin();

	for (it; it < mWeapons.end(); ++it)
	{
		if ((*it)->GetIsEquiped())
		{
			(*it)->SetIsEquiped(false);

			if (it == mWeapons.end() - 1)
			{
				it = mWeapons.begin();

				(*it)->SetIsEquiped(true);
			}
			else
			{
				(*(it + 1))->SetIsEquiped(true);
			}
			break;
		}
	}
}

Weapon* Player::GetCurrentEquipedWeapon()
{
	for (Weapon* w : mWeapons)
	{
		if (w->GetIsEquiped() == true)
			return w;
	}
}
