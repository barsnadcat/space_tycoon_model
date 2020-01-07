#pragma once

#include "Person.h"

#include <vector>
#include <memory>

class Settlement
{
private:
	std::vector<std::shared_ptr<Person>> mPeople;
};
