#pragma once

#include <Entity.h>
#include <Item.h>

class Food: public Item
{
public:
	Food(Entity* prev, uint32_t health): Item(kFoodId, prev, health, 1) {}
	int32_t GetEnergy() { return 3; }
};
