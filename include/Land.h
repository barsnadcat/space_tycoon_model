#pragma once

#include <Entity.h>
#include <memory>

class Settlement;
class Farm;
class Food;
using Foods = std::vector<Food*>;
class Person;
using People = std::vector<Person*>;


class Land: public Entity
{
public:
	Land(Settlement* settlement, size_t index);
	virtual ~Land();

	Settlement* GetSettlement() const { return mSettlement; }
	size_t GetIndex() const { return mIndex; }

	Farm* GetFarm() { return mFarm; }
	void AddFarm(Farm* farm);
	void RemoveFarm(Farm* farm);

	const Foods& GetFoods() const { return mFoods; }
	void AddFood(Food* food);
	void RemoveFood(Food* food);

	People& GetPeople() { return mPeople; }
	void AddPerson(Person* person);
	void RemovePerson(Person* person);

private:
	Settlement* const mSettlement = nullptr;
	const size_t mIndex = 0;
	Farm* mFarm = nullptr;
	Foods mFoods = {};
	People mPeople = {};
};
