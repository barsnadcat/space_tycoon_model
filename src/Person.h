#pragma once

#include "IEntity.h"
#include "Food.h"

#include <vector>
#include <memory>

class Person: public IEntity
{
public:
	using Shared = std::shared_ptr<Person>;

	Person(uint32_t health, int32_t energy): IEntity(health), mEnergy(energy) {}
	void AddFood(std::shared_ptr<Food> food) { mFoods.push_back(food); }
private:
	virtual void EntityChildUpdate() override;
private:
	std::vector<Food::Shared> mFoods;
	int32_t mEnergy { 0 };
};

