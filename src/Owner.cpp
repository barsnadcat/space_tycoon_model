#include <Owner.h>

#include <Building.h>
#include <Food.h>
#include <Farm.h>

Owner::Owner(Entity* prev, uint32_t health, uint32_t decayRate): Entity(prev, health, decayRate)
{
}

Owner::~Owner()
{
	if (mBuilding)
	{
		mBuilding->RemoveOwner(this);
	}
	for (auto p : mFoods)
	{
		p->SetOwner(nullptr);
		delete p;
	}
}

void Owner::AddFood(Food* food)
{
	assert(food);
	food->SetOwner(this);
	mFoods.push_back(food);
}

void Owner::RemoveFood(Food* food)
{
	assert(food);
	food->SetOwner(nullptr);
	mFoods.erase(std::remove(mFoods.begin(), mFoods.end(), food), mFoods.end());
}

void Owner::MoveTo(Owner& target)
{
	for (auto p : mFoods)
	{
		target.AddFood(p);
	}
	mFoods.clear();
}

void Owner::OnEntityDeath(UpdateContext& uc)
{
	MoveTo(mBuilding->GetNullOwner());
}
