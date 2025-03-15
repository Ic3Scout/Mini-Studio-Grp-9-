#pragma once

class Player;

class AmmoBar
{
	Player* pOwner; 

public:
	void UpdateBar();

	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
};

