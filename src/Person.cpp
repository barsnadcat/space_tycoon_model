#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Building.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
    // Claim food from parent space
	Space* parent = GetParent();
	if (parent)
	{
		std::bernoulli_distribution distribution(0.5);
		if (distribution(uc.mRandomEngine))
		{
			int claimed = 0;
			for (FoodPtr& food : parent->GetFoods())
			{
				if (food->GetOwner() == nullptr)
				{
					claimed++;
					ClaimFood(food);
					if (claimed == 3)
					{
						break;
					}
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
	FoodPtr food = GetMyNearFood();
	if (food)
    {
        mEnergy = std::min(kMaxEnergy, mEnergy + food->GetEnergy());
		if (Space* foodSpace = food->GetParent())
		{
			auto& vec = foodSpace->GetFoods();
			vec.erase(std::remove(vec.begin(), vec.end(), food), vec.end());
		}
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
