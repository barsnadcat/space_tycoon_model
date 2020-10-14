#include "Person.h"

#include <UpdateContext.h>
#include <Building.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
    // Pickup food	
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

	// Claim. Where the person is? Can person be inside building?
	// If person can be inside building it makes a lot of interactions a lot more complicated. 
	// I.e. to trade with other person you need to go to parent and child spaces, same with claim.

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
