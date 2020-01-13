#pragma once

#include "IEntity.h"
#include "Food.h"

#include <vector>
#include <memory>

class Person: public IEntity
{
public:
	Person(uint32_t health, int32_t energy): IEntity(health), mEnergy(energy) {}
	void Update(const uint32_t days);

private:
	std::vector<std::shared_ptr<Food>> mFoods;
	int32_t mEnergy { 0 };
};

