#include <Land.h>

#include <Farm.h>
#include <Food.h>
#include <Person.h>
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
}

void Land::RemoveFarm(Farm* p)
{
	assert(mFarm == p);
	mFarm->SetLand(nullptr);
	mFarm = nullptr;
}

void Land::AddFarm(Farm* p)
{
	assert(p);
	assert(mFarm == nullptr);
	mFarm = p;
}

void Land::AddFood(Food* food)
{
	assert(food);
	mFoods.push_back(food);
}

void Land::RemoveFood(Food* food)
{
	assert(food);
	food->SetLand(nullptr);
	mFoods.erase(std::remove(mFoods.begin(), mFoods.end(), food), mFoods.end());
}

void Land::AddPerson(Person* p)
{
	assert(p);
	mPeople.push_back(p);
}

void Land::RemovePerson(Person* p)
{
	assert(p);
	p->SetLand(nullptr);
	mPeople.erase(std::remove(mPeople.begin(), mPeople.end(), p), mPeople.end());
}
