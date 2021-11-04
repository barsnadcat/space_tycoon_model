#pragma once

#include <Entity.h>
#include <Item.h>

class Food: public Item
{
public:
	Food(Entity* prev, uint32_t health): Item(prev, health, 1, kFoodId) {}
	int32_t GetEnergy() { return 3; }
};

using FoodPtr = std::unique_ptr<Food>;