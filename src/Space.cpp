#include "Space.h"

#include "Food.h"
#include "Person.h"

template<typename T>
void Space::DeleteEntities(std::vector<std::unique_ptr<T>>& container)
{
	for (auto it = container.begin(); it != container.end();)
	{
		Entity& entity = **it;
		if (entity.GetHealth() == 0)
		{
			entity.MoveTo(*this);
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
	for (auto& p : mPeople)
	{
		p->Update(uc);
	}
	for (auto& p : mFoods)
	{
		p->Update(uc);
	}
	DeleteEntities(mPeople);
	DeleteEntities(mFoods);
	OnSpaceUpdated(uc);
}

void Space::AddPerson(PersonPtr p)
{
	p->SetParent(this);
	mPeople.push_back(std::move(p));
}
void Space::AddFood(FoodPtr p)
{
	p->SetParent(this);
	mFoods.push_back(std::move(p));
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
}
