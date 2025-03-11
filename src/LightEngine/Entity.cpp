#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

void Entity::Initialize(float radius, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setRadius(radius);
	mShape.setFillColor(color);
	
	mTarget.isSet = false;

	OnInitialize();
}

void Entity::Repulse(Entity* other) 
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);
	
	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);

	float radius1 = mShape.getRadius();
	float radius2 = other->mShape.getRadius();

	float overlap = (length - (radius1 + radius2)) * 0.5f;

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = overlap * normal;

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	SetPosition(position1.x, position1.y, 0.5f, 0.5f);
	other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
}

int Entity::IsColliding(Entity* other) const
{
	AABBCollider HB = mHitbox;
	AABBCollider otherHB = *(other->GetHitbox());

	if (HB.xMax >= otherHB.xMin && HB.xMin <= otherHB.xMax)
	{
		if(HB.yMax >= otherHB.yMin && HB.yMin <= otherHB.yMax)
		{
			int mFace = 0;
			//Face Detection

			float overlapX = 0;
			float overlapY = 0;

			sf::Vector2f distBetweenCentersXY = { abs( this->GetPosition().x - other->GetPosition().x ) , abs( this->GetPosition().y - other->GetPosition().y ) };

			float halfWidth = (abs(HB.xMax - HB.xMin)) *0.5f;
			float halfHeight = (abs(HB.yMax - HB.yMin)) * 0.5f;

			float otherHalfWidth = (abs(otherHB.xMax - otherHB.xMin)) * 0.5f;
			float otherHalfHeight = (abs(otherHB.yMax - otherHB.yMin)) * 0.5f;

			overlapX = halfWidth + otherHalfWidth - distBetweenCentersXY.x;
			overlapY = halfHeight + otherHalfHeight - distBetweenCentersXY.y;

			//std::cout << "Overlap X = " << overlapX << "\nOverlap Y = " << overlapY << std::endl;

			if (overlapX > overlapY)
			{
				if (HB.yMax < otherHB.yMax)
				{
					mFace = CollideWith::Bottom;
				}
				else
				{
					mFace = CollideWith::Top;
				}
			}
			else
			{
				if (HB.xMax < otherHB.xMax)
				{
					mFace = CollideWith::Right;
				}
				else
					mFace = CollideWith::Left;
			}

			return mFace;
		}
	}

	system("cls");

	return CollideWith::Nothing;
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mShape.getRadius();

	return (dx * dx + dy * dy) < (radius * radius);
}

void Entity::UpdateHitBox()
{
	sf::Vector2f pos = GetPosition();

	AABBCollider h = mHitbox;

	float width = (h.xMax - h.xMin);
	float height = (h.yMax - h.yMin);

	if (width <= 0 || height <= 0)
	{
		std::cout << "Error : Invalid Width or Height !\n";
		return;
	}

	mHitbox.xMin = pos.x - width * 0.5f;
	mHitbox.yMin = pos.y - height * 0.5f;

	mHitbox.xMax = pos.x + width * 0.5f;
	mHitbox.yMax = pos.y + height * 0.5f;

	Debug::DrawRectangle(mHitbox.xMin, mHitbox.yMin, width, height, sf::Color::Blue);
}

void Entity::SetHitbox(float xMin, float yMin, float xMax, float yMax)
{
	if (xMax - xMin < 0 || yMax - yMin < 0)
	{
		std::cout << "Impossible to set hitbox !\n";
		return;
	}

	mHitbox.xMin = xMin;
	mHitbox.yMin = yMin;
	mHitbox.xMax = xMax;
	mHitbox.yMax = yMax;
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	float size = mShape.getRadius() * 2;

	x -= size * ratioX;
	y -= size * ratioY;

	mShape.setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	float size = mShape.getRadius() * 2;
	sf::Vector2f position = mShape.getPosition();

	position.x += size * ratioX;
	position.y += size * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	mShape.move(translation);

	if (mTarget.isSet) 
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	UpdateHitBox();

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}