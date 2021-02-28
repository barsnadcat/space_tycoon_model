#pragma once

#include <Object.h>
#include <Entity.h>
#include <Property.h>

class Food: public Object
{
public:
	Food(uint32_t health)
	{
		mEntity = std::make_unique<Entity>(health);
		mProperty = std::make_unique<Property>();
	}
	int32_t GetEnergy() { return 3; }
};
