#pragma once

#include "Entity.h"

class Food: public Entity
{
	using Entity::Entity;

public:
	using Shared = std::shared_ptr<Food>;
	int32_t GetEnergy() { return 2; }
};
