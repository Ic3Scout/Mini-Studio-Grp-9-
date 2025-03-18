#include "Enemy.h"
#include "Player.h"
#include "TestScene.h"

Enemy::Enemy(int maxHP) : Character(maxHP)
{
	player = GetScene<TestScene>()->GetPlayer();
}

void Enemy::OnInitialize()
{
	SetTag(TestScene::TEnemy);
}
