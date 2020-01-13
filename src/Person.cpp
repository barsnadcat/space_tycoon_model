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

	// Eat
	int foodToEat = days;
	while (!mFoods.empty() && foodToEat)
	{
		std::shared_ptr<Food> food = mFoods.back();
		mFoods.pop_back();
		mEnergy--;
		mEnergy = std::max(mEnergy + food->GetEnergy(), kMaxEnergy);
		foodToEat--;
	}
	mEnergy = mEnergy - foodToEat;

	// Update biology
	DecayMaxHealth(days);
	if (mEnergy < 0)
	{
		SetHealth(GetHealth() + mEnergy);
		mEnergy = 0;
	}
}
