#include <Building.h>

#include <Owner.h>
#include <Land.h>

Building::Building(Entity* prev, uint32_t health, uint32_t decayRate): Entity(prev, health, decayRate)
{
	mNullOwner.reset(new Owner(this, 1, 0));
	mNullOwner->SetBuilding(this);
}

Building::~Building()
{
	if (mLand)
	{
		mLand->RemoveBuilding(this);
	}
	for (Owner* p : mOwners)
	{
		p->SetBuilding(nullptr);
		delete p;
	}
	mNullOwner->SetBuilding(nullptr);
}

void Building::AddOwner(Owner* owner)
{
	assert(owner);
	owner->SetBuilding(this);
	mOwners.push_back(owner);
}

void Building::RemoveOwner(Owner* owner)
{
	assert(owner);
	owner->SetBuilding(nullptr);
	mOwners.erase(std::remove(mOwners.begin(), mOwners.end(), owner), mOwners.end());
}

void Building::MoveTo(Building& target)
{
	for (Owner* p : mOwners)
	{
		target.AddOwner(p);
	}
	mOwners.clear();

	mNullOwner->MoveTo(target.GetNullOwner());
}

void Building::OnEntityDeath(UpdateContext& uc)
{
	MoveTo(mLand->GetNullBuilding());
}
