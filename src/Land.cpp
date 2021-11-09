#include <Land.h>

#include <Building.h>
#include <Space.h>
#include <cassert>

Land::Land(Space* space, size_t index): Entity(space, 1, 0), mSpace(space), mIndex(index)
{
	mBuilding.reset(new Building(this, 1, 0));
	mNullBuilding->SetLand(this);
}

Land::~Land()
{
	mBuilding->SetLand(nullptr);
}

void Land::RemoveBuilding(Building* building)
{
	assert(mBuilding.get() == building);
	AddBuilding(new Building(this, 1, 0));
}

void Land::AddBuilding(Building* newBuilding)
{
	mBuilding->MoveTo(*newBuilding);
	mBuilding->SetLand(nullptr);
	newBuilding->SetLand(this);
	mBuilding.reset(newBuilding);
}
