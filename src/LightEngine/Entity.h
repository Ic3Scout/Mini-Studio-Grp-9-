#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
	struct AABBCollider
	{
		int face = 0;

		bool isActive = true;

		float xMin, yMin;
		float xMax, yMax;

		float offsetX = 0.f, offsetY = 0.f;

		sf::Vector2f size;
	};

    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::RectangleShape mShape;
    sf::Vector2f mDirection;
	AABBCollider mHitbox;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

public:
	enum CollideWith
	{
		Nothing,
		Left,
		Top,
		Right,
		Bottom,
	};

	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	sf::Vector2f GetSize() const { return mShape.getSize(); }
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other);
	bool IsInside(float x, float y) const;

	//Changes
	AABBCollider* GetHitbox() { return &mHitbox; }
	void UpdateHitBox();
	void SetHitbox(float width, float height);
	void SetHitboxOffset(float offsetX, float offsetY);
	void SetIsHitboxActive(bool result = true) { mHitbox.isActive = result; }

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};

private:
    void Update();
	void Initialize(sf::Vector2f size, const sf::Color& color);
	void Repulse(Entity* other);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"