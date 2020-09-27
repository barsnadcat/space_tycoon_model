#include "Person.h"

#include <UpdateContext.h>
#include <Building.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
    // Pickup
	Space* parent = GetParent();
	if (parent)
	{
		std::bernoulli_distribution distribution(0.5);
		if (distribution(uc.mRandomEngine))
		{
			for (int i = 0; i < 3; i++)
			{
				if (!parent->GetFoods().empty())
				{
					Foods::iterator it = --parent->GetFoods().end();
					AddFood(*it);
					parent->GetFoods().erase(it);
				}
			}
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

    // Procreation
	if (parent && mEnergy > 100)
	{
		std::bernoulli_distribution distribution(0.25);
		if (distribution(uc.mRandomEngine))
		{
			mEnergy = 0;
			parent->AddPerson(std::make_shared<Person>(30000, 0));
		}
	}
}
