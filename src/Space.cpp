#include "Space.h"

#include "Food.h"
#include "Person.h"

template <typename T>
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

void Space::Update()
{
	for (auto& p : mPeople)
	{
		p->Update();
	}
	for (auto& p : mFoods)
	{
		p->Update();
	}
	DeleteEntities(mPeople);
	DeleteEntities(mFoods);
	OnSpaceUpdated();
}

void Space::MoveTo(Space& destination)
{
	std::move(mFoods.begin(), mFoods.end(), std::back_inserter(destination.mFoods));
	std::move(mPeople.begin(), mPeople.end(), std::back_inserter(destination.mPeople));
}
