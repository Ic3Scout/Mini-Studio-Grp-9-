#include "PlayerAction.h"
#include "Player.h"

bool PlayerAction::Move(Player* pPlayer)
{
	if (pPlayer->mIsMoving)
		return true;

	pPlayer->mIsMoving = 0.f;
	return false;
}

void PlayerAction_Idle::Start(Player* pPlayer)
{
}

void PlayerAction_Idle::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Idle" << std::endl;

	if (pPlayer->mGravityAcceleration != 0 && pPlayer->mGravitySpeed > 50.f && pPlayer->mHitbox.face != Player::CollideWith::Bottom)
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
	sf::Vector2f pos = pPlayer->GetPosition();
	pPlayer->SetPosition(pos.x + *speed * deltatime * pPlayer->GetSide(), pos.y);

	if (pPlayer->mIsMoving == false)
		pPlayer->TransitionTo(Player::Idle);


	if (pPlayer->mGravityAcceleration != 0 && pPlayer->mGravitySpeed > 50.f && pPlayer->mHitbox.face != Player::CollideWith::Bottom)
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

	pPlayer->mGravitySpeed = -std::sqrt(7 * pPlayer->mGravityAcceleration * pPlayer->GetSize().y);
}

void PlayerAction_Jumping::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Jumping" << std::endl;

	pPlayer->SetGravity(true);

	if (Move(pPlayer))
	{
		float* speed = &(pPlayer->mSpeed);
		*speed += pPlayer->mParameters.mAcceleration * deltatime;
		if (*speed > pPlayer->mParameters.mMaxSpeed)
		{
			*speed = pPlayer->mParameters.mMaxSpeed;
		}
		sf::Vector2f pos = pPlayer->GetPosition();
		pPlayer->SetPosition(pos.x + pPlayer->mSpeed * deltatime * pPlayer->GetSide(), pos.y);
	}

	if (pPlayer->mGravityAcceleration != 0 && pPlayer->mGravitySpeed >= 0)
	{
		pPlayer->TransitionTo(Player::Falling); 
	}
}



void PlayerAction_Falling::Start(Player* pPlayer)
{

}

void PlayerAction_Falling::Update(Player* pPlayer, float deltatime)
{
	std::cout << "Falling" << std::endl;

	bool isMoving = false;

	isMoving = Move(pPlayer);

	if (isMoving)
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

	if (pPlayer->mGravityAcceleration == 0 && pPlayer->mGravitySpeed < 50.f && isMoving == false) 
	{
		pPlayer->TransitionTo(Player::Idle); 
	}
	else if (pPlayer->mGravityAcceleration == 0 && pPlayer->mGravitySpeed < 50 && isMoving == true)
	{
		pPlayer->TransitionTo(Player::Moving);  
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
	sf::Vector2f pos = pPlayer->GetPosition();

	if (mDuration > 0)
	{
		if (pPlayer->mHitbox.face != Player::CollideWith::Left && pPlayer->mHitbox.face != Player::CollideWith::Right)
		{
			pPlayer->SetGravity(false);

			pPlayer->SetPosition(pos.x + *speedBoost * deltatime * pPlayer->GetSide(), pos.y);
		
		}
		else
			mDuration = 0.f;
	}
	else
	{
		pPlayer->SetGravity(true);

		*speedBoost = 0.f;

		pPlayer->TransitionTo(Player::Falling);
	}

	mDuration -= deltatime;
}


