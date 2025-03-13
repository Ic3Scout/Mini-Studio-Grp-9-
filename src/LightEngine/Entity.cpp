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

bool Entity::IsColliding(Entity* other)
{
	AABBCollider& hb = mHitbox;
	AABBCollider& otherHb = *(other->GetHitbox()); 

	if (hb.isActive == false || otherHb.isActive == false)
	{
		return false;
	}

	float hbWidth = abs(hb.xMax - hb.xMin); 
	float hbHeight = abs(hb.yMax - hb.yMin); 

	float otherHBWidth = abs(otherHb.xMax - otherHb.xMin); 
	float otherHBHeight = abs(otherHb.yMax - otherHb.yMin); 

	if (hbWidth <= 0 || hbHeight <= 0 || otherHBWidth <= 0 || otherHBHeight <= 0)
	{
		return false; 
	} 

	if (hb.xMax >= otherHb.xMin && hb.xMin <= otherHb.xMax)
	{
		if(hb.yMax >= otherHb.yMin && hb.yMin <= otherHb.yMax)
		{
			//Face Detection

			float overlapX = 0;
			float overlapY = 0;

			sf::Vector2f pos = GetPosition();
			sf::Vector2f otherPos = other->GetPosition();

			sf::Vector2f distBetweenCentersXY = { abs( pos.x + hb.offsetX - otherPos.x - otherHb.offsetX) , abs( pos.y + hb.offsetY - otherPos.y - otherHb.offsetY) }; 

			float halfWidth = hbWidth * 0.5f; 
			float halfHeight = hbHeight * 0.5f; 

			overlapX = hbWidth * 0.5f + otherHBWidth * 0.5f - distBetweenCentersXY.x;
			overlapY = hbHeight * 0.5f + otherHBHeight * 0.5f - distBetweenCentersXY.y;

			if (overlapX > overlapY)
			{
				if (hb.yMax < otherHb.yMax)
				{
					hb.face = CollideWith::Bottom;
					otherHb.face = CollideWith::Top;
				}
				else
				{
					hb.face = CollideWith::Top;
					otherHb.face = CollideWith::Bottom;
				}
			}
			else
			{
				if (hb.xMax < otherHb.xMax)
				{
					hb.face = CollideWith::Right;
					otherHb.face = CollideWith::Left;
				}
				else
				{
					hb.face = CollideWith::Left;
					otherHb.face = CollideWith::Right;
				}
			}

			return true;
		}
	}

	return false;
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
	if (mHitbox.isActive == false)
		return;

	sf::Vector2f pos = GetPosition();

	AABBCollider h = mHitbox;

	float width = (h.xMax - h.xMin);
	float height = (h.yMax - h.yMin);

	if (width <= 0 || height <= 0)
	{
		return;
	}

	mHitbox.xMin = pos.x - width * 0.5f + mHitbox.offsetX;
	mHitbox.yMin = pos.y - height * 0.5f + mHitbox.offsetY;

	mHitbox.xMax = pos.x + width * 0.5f + mHitbox.offsetX;
	mHitbox.yMax = pos.y + height * 0.5f + mHitbox.offsetY;

	Debug::DrawRectangle(mHitbox.xMin, mHitbox.yMin, width, height, sf::Color::Blue);
}

void Entity::SetHitbox(float width, float height)
{
	if (width < 0 || height < 0)
	{
		std::cout << "Impossible to set hitbox !\n";
		return;
	}

	mHitbox.xMin = -width * 0.5f;
	mHitbox.yMin = -height * 0.5f;
	mHitbox.xMax = width * 0.5f;
	mHitbox.yMax = height * 0.5f;
}

void Entity::SetHitboxOffset(float offsetX, float offsetY)
{
	mHitbox.offsetX = offsetX;
	mHitbox.offsetY = offsetY;
}

void Entity::ChangeColor(sf::Color newColor)
{
	mShape.setFillColor(newColor);
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