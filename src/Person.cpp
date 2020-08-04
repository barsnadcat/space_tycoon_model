#include "Person.h"

const int kMaxEnergy = 30;

void Person::OnEntityUpdated()
{
	// Eat
	VectorSpaceIterator<Food> foodIt = GetFoodIterator();
	if (foodIt.HasNext())
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + foodIt.Get().GetEnergy());
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
