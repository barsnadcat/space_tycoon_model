#include <Space.h>

#include <Settlement.h>
#include <Owner.h>
#include <Food.h>
#include <Person.h>
#include <Farm.h>

void UpdateObjects(ObjectSPs& container, UpdateContext& uc)
{
	for (ObjectSP object : container)
	{
		object->Update(uc);
	}
}

void DeleteObjects(ObjectSPs& container)
{
	auto predicate = [](auto const& p)
					 {
						 return p->mEntity->GetHealth() == 0;
					 };
	container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}

void Space::Update(UpdateContext& uc)
{
	UpdateObjects(mPeople, uc);
	UpdateObjects(mProducts[kFoodId], uc);
	UpdateObjects(mProducts[kFarmId], uc);
	DeleteObjects(mPeople);
	DeleteObjects(mProducts[kFoodId]);
	DeleteObjects(mProducts[kFarmId]);
}

void Space::AddPerson(ObjectSP p)
{
	p->mEntity->SetParent(mThisObject.lock());
	mPeople.push_back(p);
}

void Space::AddFood(ObjectSP p)
{
	p->mEntity->SetParent(mThisObject.lock());
	mProducts[kFoodId].push_back(p);
}

void Space::AddBuilding(ObjectSP p)
{
	p->mEntity->SetParent(mThisObject.lock());
	mProducts[kFarmId].push_back(p);
}

void Space::MoveTo(ObjectSP destination)
{
	for (auto& p : mProducts[kFoodId])
	{
		p->mEntity->SetParent(destination);
	}
	std::move(mProducts[kFoodId].begin(), mProducts[kFoodId].end(), std::back_inserter(destination->mSpace->mProducts[kFoodId]));

	for (auto& p : mPeople)
	{
		p->mEntity->SetParent(destination);
	}
	std::move(mPeople.begin(), mPeople.end(), std::back_inserter(destination->mSpace->mPeople));

	for (auto& p : mProducts[kFarmId])
	{
		p->mEntity->SetParent(destination);
	}
	std::move(mProducts[kFarmId].begin(), mProducts[kFarmId].end(), std::back_inserter(destination->mSpace->mProducts[kFarmId]));
}
