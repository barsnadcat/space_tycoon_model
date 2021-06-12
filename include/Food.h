#pragma once

#include <Entity.h>
#include <Item.h>


class Food: public Item
{
public:
	Food(uint32_t health): Item(health, 1) {}
	int32_t GetEnergy() { return 3; }
};

using FoodPtr = std::unique_ptr<Food>;
