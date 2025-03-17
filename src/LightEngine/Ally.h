#pragma once
#include "PhysicalEntity.h"

class Ally : public PhysicalEntity
{
public:
	enum TagAlly
	{
		TVineR,
		TVineG,
		TNenuphloatR,
		TNenuphloatG,
		TStation,
		TBulb,
	};
	virtual void OnInitialize();

	void SetTagAlly(int tagAlly) { mTagAlly = tagAlly; }

	bool IsTagAlly(int tagAlly);
};

