#include "Person.h"
#include "UpdateContext.h"

const int kMaxEnergy = 30;

void Person::OnEntityUpdated(UpdateContext& uc)
{
    // Pickup. Lol we need parent!
	Space* parent = GetParent();
	if (parent)
	{
		std::uniform_int_distribution<int> distribution(0, 1);		
		if (!parent->GetFoods().empty() && distribution(uc.mRandomEngine))
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
