#include <Space.h>

#include <Entity.h>

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
						 return p->entity->GetHealth() == 0;
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
	p->entity->SetParent(mThisObject.shared_from_this());
	mPeople.push_back(p);
}

void Space::AddFood(ObjectSP p)
{
	p->entity->SetParent(mThisObject.shared_from_this());
	mProducts[kFoodId].push_back(p);
}

void Space::AddBuilding(ObjectSP p)
{
	p->entity->SetParent(mThisObject.shared_from_this());
	mProducts[kFarmId].push_back(p);
}

void Space::MoveTo(ObjectSP destination)
{
	for (auto& p : mProducts[kFoodId])
	{
		p->entity->SetParent(destination);
	}
	std::move(mProducts[kFoodId].begin(), mProducts[kFoodId].end(), std::back_inserter(destination->space->mProducts[kFoodId]));

	for (auto& p : mPeople)
	{
		p->entity->SetParent(destination);
	}
	std::move(mPeople.begin(), mPeople.end(), std::back_inserter(destination->space->mPeople));

	for (auto& p : mProducts[kFarmId])
	{
		p->entity->SetParent(destination);
	}
	std::move(mProducts[kFarmId].begin(), mProducts[kFarmId].end(), std::back_inserter(destination->space->mProducts[kFarmId]));
}
