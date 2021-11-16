#include <Land.h>

#include <Building.h>
#include <Settlement.h>
#include <cassert>

Land::Land(Settlement* settlement, size_t index): Entity(settlement, 1, 0), mSettlement(settlement), mIndex(index)
{
	mNullBuilding.reset(new Building(this, 1, 0));
	mNullBuilding->SetLand(this);
}

Land::~Land()
{
	mNullBuilding->SetLand(nullptr);

	if (mBuilding)
	{
		mBuilding->SetLand(nullptr);
		delete mBuilding;
	}
}

void Land::RemoveBuilding(Building* building)
{
	assert(mBuilding == building);
	mBuilding->SetLand(nullptr);
	mBuilding = nullptr;
}

void Land::AddBuilding(Building* building)
{
	assert(mBuilding == nullptr);
	mBuilding = building;
	mBuilding->SetLand(this);
}
