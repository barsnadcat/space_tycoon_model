#pragma once

#include <Object.h>

class Food
{
public:
	int32_t GetEnergy() { return 3; }
};

ObjectSP ConstructFood(uint32_t health);
