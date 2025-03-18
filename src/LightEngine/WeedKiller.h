#pragma once
#include "Entity.h"
#include "Weapon.h"

class WeedKiller : public Weapon
{

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void FixedUpdate(float dt) override;
	void OnDestroy() override;
	void Shoot() override;
};

