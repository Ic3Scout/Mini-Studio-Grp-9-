#include "PlayerAction.h"
#include "Player.h"

bool PlayerAction::Move(Player* pPlayer)
{
	bool isMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || pPlayer->mJoyX > 25)
	{
		isMoving = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || pPlayer->mJoyX < -25)
		{
			isMoving = false;
		}
		else
		{
			pPlayer->mSide = 1;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || pPlayer->mJoyX < -25)
	{
		isMoving = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || pPlayer->mJoyX > 25)
		{
			isMoving = false;
		}
		else
		{
			pPlayer->mSide = -1;
		}
	
	}

	if (isMoving == false)
	{
		pPlayer->mSpeed = 0;
	}

	return isMoving;
}

void PlayerAction_Idle::Start(Player* pPlayer)
{

}

void PlayerAction_Idle::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Idle" << std::endl;
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
	sf::Vector2f pos =  pPlayer->GetPosition();
	pPlayer->SetPosition(pos.x + *speed * deltatime * pPlayer->GetSide(), pos.y);
}



void PlayerAction_Jumping::Start(Player* pPlayer)
{
	pPlayer->mHitbox.face = pPlayer->CollideWith::Nothing;

	pPlayer->mGravitySpeed = -std::sqrt(7 * pPlayer->mGravityAcceleration * pPlayer->GetSize().y); 
}

void PlayerAction_Jumping::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Jumping" << std::endl;

	if (Move(pPlayer))
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}

	
	}

	sf::Vector2f pos = pPlayer->GetPosition();
	pPlayer->SetPosition(pos.x + pPlayer->mSpeed * deltatime * pPlayer->GetSide(), pos.y);

	if (pPlayer->mGravity > 0)
	{
		pPlayer->TransitionTo(pPlayer->State::Falling);
	}
}



void PlayerAction_Falling::Start(Player* pPlayer)
{

}

void PlayerAction_Falling::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Falling" << std::endl;

	if (Move(pPlayer))
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}

	}

	sf::Vector2f pos = pPlayer->GetPosition();
	pPlayer->SetPosition(pos.x + pPlayer->mSpeed * deltatime * pPlayer->GetSide(), pos.y);

	if (pPlayer->mGravity == 0 && pPlayer->mHitbox.face == pPlayer->CollideWith::Bottom && pPlayer->mState != pPlayer->Jumping)
	{

	}
		//pPlayer->TransitionTo(pPlayer->Idle);
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
	std::cout << "Dying" << std::endl;
}

void PlayerAction_Dying::Update(Player* pPlayer, float deltatime)
{

}



void PlayerAction_Dashing::Start(Player* pPlayer)
{
	std::cout << "Dashing" << std::endl;
}

void PlayerAction_Dashing::Update(Player* pPlayer, float deltatime)
{

}


