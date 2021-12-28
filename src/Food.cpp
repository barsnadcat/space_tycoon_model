#include <Food.h>

#include <Land.h>
#include <Person.h>

Food::Food(Land* land, uint32_t health): Entity(land, health, 1)
{
	assert(land);
	mLand = land;
	mLand->AddFood(this);
}

Food::~Food()
{
	if (mLand)
	{
		mLand->RemoveFood(this);
	}

	if (mPerson)
	{
		mPerson->RemoveFood(this);
	}
}
