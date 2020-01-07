#pragma once

#include "IEntity.h"
#include "Food.h"

#include <vector>
#include <memory>

class Person: public IEntity
{
private:
	std::vector<std::shared_ptr<Food>> mFoods;
};