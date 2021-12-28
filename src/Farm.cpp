#include <Farm.h>

#include <Land.h>
#include <Person.h>

Farm::Farm(Land* land, uint32_t health): Entity(land, health, 1)
{
	assert(land);
	mLand = land;
	land->AddFarm(this);
}

Farm::~Farm()
{
	if (mLand)
	{
		mLand->RemoveFarm(this);
	}

	if (mPerson)
	{
		mPerson->RemoveFarm(this);
	}
}
