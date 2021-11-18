#include <Food.h>

#include <Land.h>

Food::~Food()
{
	if (mLand)
	{
		mLand->RemoveFood(this);
	}
}
