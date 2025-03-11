#pragma once

class Collider
{
public:
	virtual bool IsColliding(Collider* pOther) = 0;

};

