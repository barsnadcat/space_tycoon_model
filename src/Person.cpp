#include "Person.h"

const int kMaxEnergy = 30;

void Person::Update(const uint32_t days)
{
	// Invetroy update
	for(auto& foodPtr: mFoods)
	{
		foodPtr->DecayMaxHealth(days);
	}
	RemoveDead<Food>(mFoods);

	

	for (uint32_t i = 0; i < days; ++i)
	{
		DecayMaxHealth(1);
		
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
			SetHealth(GetHealth() - 1);
		}
		else
		{
			mEnergy--;
		}
	}
}
