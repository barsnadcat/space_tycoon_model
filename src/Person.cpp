#include "Person.h"

void Person::Update(const uint32_t days)
{
	for(auto& foodPtr: mFoods)
	{
		foodPtr->DecayMaxHealth(days);
	}
	RemoveDead<Food>(mFoods);
	DecayMaxHealth(days);
	mEnergy = mEnergy - days;
	if (mEnergy < 0)
	{
		SetHealth(GetHealth() + mEnergy);
		mEnergy = 0;
	}
}
