#pragma once

#include "Person.h"
#include "Space.h"

#include <vector>
#include <memory>

class Settlement: public Space
{
public:
	virtual IEntityIterator::Shared GetEntityIterator() { return std::make_shared<VectorEntityIterator<Person::Shared>>(mPeople); }

	void AddPerson(Person::Shared person) { mPeople.push_back(person); }
private:
	std::vector<Person::Shared> mPeople;
};
