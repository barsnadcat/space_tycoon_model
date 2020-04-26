#include "Person.h"

const int kMaxEnergy = 30;

void Person::EntityChildUpdate()
{
	// Eat
	VectorSpaceIterator<Food> foodIt = GetFoodIterator();
	if (foodIt.HasNext())
	{
		mEnergy = std::max(kMaxEnergy, mEnergy + foodIt.Get().GetEnergy());
		foodIt.Remove();
	}

	// Expend energy or hunger damage
	if (mEnergy == 0)
	{
		DamageHealth(1);
	}
	else
	{
		mEnergy--;
	}
}
