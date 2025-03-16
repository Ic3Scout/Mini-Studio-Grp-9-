#pragma once

class Player;

class PlayerUI
{
protected:
	bool mDisplay = true;
	Player* pOwner;
	
public:
	virtual void UpdateUI() = 0; 
	void SetOwner(Player* pPlayer) { pOwner = pPlayer; }
};

