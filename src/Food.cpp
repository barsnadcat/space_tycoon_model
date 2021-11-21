#include <Food.h>

#include <Land.h>
#include <Person.h>

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
