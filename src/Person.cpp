#include "Person.h"

const int kMaxEnergy = 30;

void Person::OnEntityUpdated()
{
	// Pickup. Lol we need parent!
	Space* parent = GetParent();
	if (parent)
	{
		if (!parent->GetFoods().empty())
		{
			Foods::iterator it = --parent->GetFoods().end();
			FoodPtr food = std::move(*it);
			parent->GetFoods().erase(it);
			AddFood(std::move(food));
		}
	}

	// Eat
	if (!GetFoods().empty())
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + GetFoods().back()->GetEnergy());
		GetFoods().pop_back();
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
