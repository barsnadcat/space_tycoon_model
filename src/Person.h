#pragma once

#include "Entity.h"
#include "Food.h"

#include <memory>
#include <vector>

class Person: public Entity
{
public:
	using Shared = std::shared_ptr<Person>;
	Person(uint32_t health, int32_t energy) : Entity(health), mEnergy(energy) {}

private:
	virtual void OnEntityUpdated() override;

private:
	int32_t mEnergy{0};
};
