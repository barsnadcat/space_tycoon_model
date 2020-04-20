#include "Person.h"

const int kMaxEnergy = 30;

void Person::EntityChildUpdate()
{
	// Eat
	if (!mFoods.empty())
	{
		std::shared_ptr<Food> food = mFoods.back();
		mFoods.pop_back();
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
