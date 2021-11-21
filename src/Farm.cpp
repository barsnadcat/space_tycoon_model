#include <Farm.h>

#include <Land.h>
#include <Person.h>

Farm::Farm(Entity* prev, uint32_t health, uint32_t decayRate): Entity(prev, health, decayRate)
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
