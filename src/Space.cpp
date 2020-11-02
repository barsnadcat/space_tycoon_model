#include "Space.h"

#include <Food.h>
#include <Person.h>
#include <Farm.h>

template<typename T>
void UpdateEntities(std::vector<std::shared_ptr<T>>& container, UpdateContext& uc)
{
	const size_t size = container.size();
	for (int i = 0; i < size; i++)
	{
		container[i]->Update(uc);
	}
}

template<typename T>
void Space::DeleteEntities(std::vector<std::shared_ptr<T>>& container)
{
	for (auto it = container.begin(); it != container.end();)
	{
		Entity& entity = **it;
		if (entity.GetHealth() == 0)
		{
			it = container.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Space::Update(UpdateContext& uc)
{
	UpdateEntities(mPeople, uc);
	UpdateEntities(mFoods, uc);
	UpdateEntities(mFarms, uc);
	DeleteEntities(mPeople);
	DeleteEntities(mFoods);
	DeleteEntities(mFarms);
	OnSpaceUpdated(uc);
}

void Space::AddPerson(PersonSP p)
{
	p->SetParent(this);
	mPeople.push_back(p);
}

void Space::AddFood(FoodSP p)
{
	p->SetParent(this);
	mFoods.push_back(p);
}

void Space::AddBuilding(FarmSP p)
{
	p->SetParent(this);
	mFarms.push_back(p);
}

void Space::MoveTo(Space& destination)
{
	for (auto& p : mFoods)
	{
		p->SetParent(&destination);
	}
	std::move(mFoods.begin(), mFoods.end(), std::back_inserter(destination.mFoods));

	for (auto& p : mPeople)
	{
		p->SetParent(&destination);
	}
	std::move(mPeople.begin(), mPeople.end(), std::back_inserter(destination.mPeople));

	for (auto& p : mFarms)
	{
		p->SetParent(&destination);
	}
	std::move(mFarms.begin(), mFarms.end(), std::back_inserter(destination.mFarms));
}
