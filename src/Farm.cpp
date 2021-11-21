#include <Farm.h>

#include <Land.h>
#include <Person.h>

Farm::Farm(Entity* prev, uint32_t health): Entity(prev, health, 1)
{
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
