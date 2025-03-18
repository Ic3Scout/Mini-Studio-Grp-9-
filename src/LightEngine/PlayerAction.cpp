#include "PlayerAction.h"
#include "Player.h"


void PlayerAction_Idle::Start(Player* pPlayer)
{
}

void PlayerAction_Idle::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Idle" << std::endl;

	if (pPlayer->GetVelocity().y >= GRAVITY_ACCELERATION)
	{
		pPlayer->TransitionTo(Player::Falling);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1)) // bouton X
	{
		pPlayer->TransitionTo(Player::Jumping);
	}

}


void PlayerAction_Moving::Start(Player* pPlayer)
{

}

void PlayerAction_Moving::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Moving" << std::endl;

	float* speed = &(pPlayer->mSpeed);
	*speed += pPlayer->mParameters.mAcceleration * deltatime;
	if (*speed > pPlayer->mParameters.mMaxSpeed)
	{
		*speed = pPlayer->mParameters.mMaxSpeed;
	}

	if (pPlayer->mIsMoving == false)
		pPlayer->TransitionTo(Player::Idle);


	if (pPlayer->GetVelocity().y > GRAVITY_ACCELERATION)
	{
		pPlayer->TransitionTo(Player::Falling);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1))// bouton X 
	{
		pPlayer->TransitionTo(Player::Jumping);
	}
}



void PlayerAction_Jumping::Start(Player* pPlayer)
{
	pPlayer->mHitbox.face = Player::CollideWith::Nothing;

	pPlayer->AddForce(sf::Vector2f(0.f, -1.f), GRAVITY_ACCELERATION, PhysicalEntity::Force::Impulse);
}

void PlayerAction_Jumping::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Jumping" << std::endl;

	if (pPlayer->mIsMoving)
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}
	}

	if (pPlayer->GetVelocity().y <= 0)
	{
		pPlayer->TransitionTo(Player::Falling);
	}
}



void PlayerAction_Falling::Start(Player* pPlayer)
{
	pPlayer->mIsGrounded = false;
}

void PlayerAction_Falling::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Falling" << std::endl;

	bool isMoving = pPlayer->mIsMoving;

	if (isMoving)
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}

	}

	if (pPlayer->mIsGrounded)
	{
		if (isMoving)
		{
			pPlayer->TransitionTo(Player::Moving);
		}
		else
		{
			pPlayer->TransitionTo(Player::Idle);
		}
	}
}



void PlayerAction_TakingDamage::Start(Player* pPlayer)
{
	std::cout << "TakingDamage" << std::endl;
	pPlayer->AddRemoveHP(-1);
}

void PlayerAction_TakingDamage::Update(Player* pPlayer, float deltatime)
{

}



void PlayerAction_Dying::Start(Player* pPlayer)
{

}

void PlayerAction_Dying::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Dying" << std::endl;
}



void PlayerAction_Dashing::Start(Player* pPlayer)
{
	mDuration = 0.2f;
}

void PlayerAction_Dashing::Update(Player* pPlayer, float deltatime)
{

	if (pPlayer->mSpeed > 0)
	{
		std::cout << " Super Dashing" << std::endl;

		pPlayer->mSpeed = 500.f;
	}
	else
	{
		std::cout << "Dashing" << std::endl;
	}

	float* speedBoost = &(pPlayer->mSpeed);
	*speedBoost += pPlayer->mParameters.mAcceleration * deltatime * 50;
	if (*speedBoost > pPlayer->mParameters.mMaxSpeed * 15)
	{
		*speedBoost = pPlayer->mParameters.mMaxSpeed;
	}

	if (mDuration > 0)
	{
		if (pPlayer->mHitbox.face != Player::CollideWith::Left && pPlayer->mHitbox.face != Player::CollideWith::Right)
		{
			pPlayer->ToggleGravity(false);
		}
		else
			mDuration = 0.f;
	}
	else
	{
		pPlayer->ToggleGravity(true);

		*speedBoost = 0.f;

		pPlayer->TransitionTo(Player::Falling);
	}

	mDuration -= deltatime;
}