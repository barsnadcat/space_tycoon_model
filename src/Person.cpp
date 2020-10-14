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
					//ClaimFood(*it);
					//parent->GetFoods().erase(it);
				}
			}
		}
	}

	// Here is problem = we still need to opeate food in our space.
	// 1 check foods space vs our space on each food
	// 2 store ownership per space. This will make movement between spaces rather complicated!
	// 3 Regardless interfaces like GetMyStuff in this space is good for us.
	// Question. What potentially can you do with property NOT in your space?
	// -- Sell it

    // Eat
	/*if (!GetMyFoods().empty())
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + GetMyFoods().back()->GetEnergy());
		GetMyFoods().pop_back();
	}*/

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
