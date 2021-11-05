#include <Food.h>

#include <Owner.h>

Food::~Food()
{
	if (mOwner)
	{
		mOwner->RemoveFood(this);
	}
}
