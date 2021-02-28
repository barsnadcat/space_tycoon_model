#pragma once

#include <Object.h>
#include <Property.h>
#include <Entity.h>

class Farm: public Object
{
public:
	Farm(uint32_t health)
	{
		mEntity = std::make_unique<Entity>(health);
		mProperty = std::make_unique<Property>();
	}
};
