#pragma once

#include "IItem.h"

class Food: public IItem
{
	using IItem::IItem;
public:
	using Shared = std::shared_ptr<Food>;
	int GetEnergy() { return 2; }
};

