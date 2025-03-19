#pragma once
#include "Ally.h"

class Bulb : public Ally
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};