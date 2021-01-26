#include "Space.h"

#include <Food.h>
#include <Person.h>
#include <Farm.h>

template<typename T>
void UpdateEntities(std::vector<std::shared_ptr<T>>& container, UpdateContext& uc)
{
	const size_t size = container.size();
	for (size_t i = 0; i < size; i++)
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
	UpdateEntities(mProducts[kFoodId], uc);
	UpdateEntities(mProducts[kFarmId], uc);
	DeleteEntities(mPeople);
	DeleteEntities(mProducts[kFoodId]);
	DeleteEntities(mProducts[kFarmId]);
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
	mProducts[kFoodId].push_back(p);
}

void Space::AddBuilding(FarmSP p)
{
	p->SetParent(this);
	mProducts[kFarmId].push_back(p);
}

void Space::MoveTo(Space& destination)
{
	for (auto& p : mProducts[kFoodId])
	{
		p->SetParent(&destination);
	}
	std::move(mProducts[kFoodId].begin(), mProducts[kFoodId].end(), std::back_inserter(destination.mProducts[kFoodId]));

	for (auto& p : mPeople)
	{
		p->SetParent(&destination);
	}
	std::move(mPeople.begin(), mPeople.end(), std::back_inserter(destination.mPeople));

	for (auto& p : mProducts[kFarmId])
	{
		p->SetParent(&destination);
	}
	std::move(mProducts[kFarmId].begin(), mProducts[kFarmId].end(), std::back_inserter(destination.mProducts[kFarmId]));
}
