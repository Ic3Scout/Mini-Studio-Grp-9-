#include "Enemy.h"
#include "TestScene.h"

Enemy::Enemy(int maxHP) : Character(maxHP)
{
	player = GetScene<TestScene>()->GetPlayer();
	parameters = player->GetParameters();
}

void Enemy::OnInitialize()
{
	SetTag(TestScene::TEnemy);
}