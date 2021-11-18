#include <Land.h>

#include <Farm.h>
#include <Settlement.h>
#include <cassert>

Land::Land(Settlement* settlement, size_t index): Entity(settlement, 1, 0), mSettlement(settlement), mIndex(index)
{
}

Land::~Land()
{
	if (mFarm)
	{
		mFarm->SetLand(nullptr);
		delete mFarm;
	}

	for (auto p : mFoods)
	{
		p->SetLand(nullptr);
		delete p;
	}

	for (auto p : mPeople)
	{
		p->SetLand(nullptr);
		delete p;
	}
}}

void Land::RemoveBuilding(Building* building)
{
	assert(mBuilding == building);
	mBuilding->SetLand(nullptr);
	mBuilding = nullptr;
}

void Land::AddBuilding(Building* building)
{
	assert(mBuilding == nullptr);
	mBuilding = building;
	mBuilding->SetLand(this);
}

void Land::AddFood(Food* food)
{
	assert(food);
	food->SetLand(this);
	mFoods.push_back(food);
}

void Land::RemoveFood(Food* food)
{
	assert(food);
	food->SetLand(nullptr);
	mFoods.erase(std::remove(mFoods.begin(), mFoods.end(), food), mFoods.end());
}

void Land::AddPerson(Person* person)
{
	assert(person);
	person->SetBuilding(this);
	mPeople.push_back(person);
}

void Land::RemovePerson(Person* person)
{
	assert(person);
	preson->SetBuilding(nullptr);
	mPeople.erase(std::remove(mPeople.begin(), mPeople.end(), person), mPeople.end());
}
