#pragma once

#include "IItem.h"

class Food: public IItem
{
	using IItem::IItem;
public:
	int GetEnergy() { return 2; }
};

