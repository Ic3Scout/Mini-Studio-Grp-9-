#pragma once
#include "PhysicalEntity.h"

class Platform : public PhysicalEntity
{
public:
	void OnInitialize() override;
	void OnCollision(Entity* other) override;
};