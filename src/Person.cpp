#include "Person.h"

const int kMaxEnergy = 30;

void Person::EntityChildUpdate()
{
	// Eat
	VectorSpaceIterator<Food> foodIt = GetFoodIterator();
	if (foodIt.HasNext())
	{
		Food::Shared food = foodIt.Get();
		foodIt.Remove();
		mEnergy = std::max(kMaxEnergy, mEnergy + food->GetEnergy());
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
