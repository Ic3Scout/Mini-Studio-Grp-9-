#include "AmmoBar.h"
#include "GameManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "TestScene.h"
#include "Player.h"
#include "Weapon.h"
#include "Debug.h"

void AmmoBar::UpdateBar()
{
	if (!pOwner)
		return;

	sf::Vector2f playerPos = pOwner->GetPosition(); 
	sf::Vector2f playerSize = pOwner->GetSize();  

	Weapon* currentWeapon = pOwner->GetCurrentEquipedWeapon();

	if (!currentWeapon)
		return;

	float ratio = currentWeapon->GetRatioMunition(); 

	sf::Color color = sf::Color::White;

	if( currentWeapon->IsTag(TestScene::TGun) )
	{
		color = sf::Color::Blue; 
	}
	else if ( currentWeapon->IsTag(TestScene::TWeedKiller) )
	{
		color = sf::Color::Green;
	}

	Debug::DrawFilledRectangle(playerPos.x - playerSize.x * 0.25f, playerPos.y - playerSize.y * 0.5f - 20, {50, 12}, sf::Color(120, 0, 0, 255));
	Debug::DrawFilledRectangle(playerPos.x - playerSize.x * 0.25f, playerPos.y - playerSize.y * 0.5f - 20, { 50 * ratio, 12 }, color);
}

