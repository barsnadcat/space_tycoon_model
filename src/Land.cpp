#include <Land.h>

#include <Building.h>
#include <Space.h>
#include <cassert>

Land::Land(Space* space, size_t index): Entity(space, 1, 0), mSpace(space), mIndex(index)
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
