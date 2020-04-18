#pragma once

#include "Person.h"
#include "IEntityContainer.h"

#include <vector>
#include <memory>

class Settlement: public IEntityContainer
{
public:
	void AddPerson(Person::Shared person) { mPeople.push_back(person); }
private:
	std::vector<Person::Shared> mPeople;
};
