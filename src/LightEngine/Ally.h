#pragma once
#include "PhysicalEntity.h"

class Ally : public PhysicalEntity
{
	int mTagAlly = - 1;
public:
	enum TagAlly
	{
		TVine,
		TStation,
		TNenuphloat,
		TBulb,
	};
	virtual void OnInitialize();

	void SetTagAlly(int tagAlly) { mTagAlly = tagAlly; }

	bool IsTagAlly(int tagAlly);
};

