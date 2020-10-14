#include "Space.h"

#include <Food.h>
#include <Person.h>
#include <Building.h>

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
	UpdateEntities(mBuildings, uc);
	DeleteEntities(mPeople);
	DeleteEntities(mFoods);
	DeleteEntities(mBuildings);
	OnSpaceUpdated(uc);
}

void Space::AddPerson(PersonPtr p)
{
	p->SetParent(this);
	mPeople.push_back(p);
}

void Space::AddFood(FoodPtr p)
{
	p->SetParent(this);
	mFoods.push_back(p);
}

void Space::AddBuilding(BuildingPtr p)
{
	p->SetParent(this);
	mBuildings.push_back(p);
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

	for (auto& p : mBuildings)
	{
		p->SetParent(&destination);
	}
	std::move(mBuildings.begin(), mBuildings.end(), std::back_inserter(destination.mBuildings));
}
