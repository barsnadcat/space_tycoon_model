#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Farm.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Space* parent = GetParent();

    // Select what to do
    // max value = 0;
    // best activity = none;
    // for all activities:
    //  n = get how much of output owned
    //  m = how muc of output is produced by activity
    //  cur value = m/n * mActivityPreference[currActivity]
    //  if curr value > max value:
    //     max value = curr value
    //     best activity = currActivity

    // We need production type enum
    // And we need product type enum
    // We need production - product association
    // We need production - tool association
    // Ie. Production1
    // Input - Product1
    // Tool - Product2
    // Outpout - quantity of Product3, quantity of Product4
    // Scavenging need this too

    // Production enum sv production object?
    // Object is closer to data driven system
    // Ojbect for product type?
    // We need production id and product id types

	bool hasFarm = false;
	if (hasFarm)
	{
		if (mLikeToFarm)
		{
            // Farm
		}
	}

	if (mLikeToBuild)
	{
        //Build
	}

    // Claim food from parent space
	std::bernoulli_distribution distribution(0.5);
	if (parent && distribution(uc.mRandomEngine))
	{
		Scavenge();
	}

    // Eat
	FoodSP food = GetMyNearFood();
	if (food)
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + food->GetEnergy());
		food->SetMaxHealth(0);
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
			parent->AddPerson(std::make_shared<Person>(30000, 0, mLikeToBuild, mLikeToFarm));
		}
	}
}

void Person::Scavenge()
{
	Space* parent = GetParent();
	assert(parent);

	if (mLikeToFarm)
	{
		for (EntitySP& farm : parent->GetFarms())
		{
			if (farm->GetOwner() == nullptr)
			{
				ClaimFarm(farm);
				return;
			}
		}
	}

	for (EntitySP& food : parent->GetFoods())
	{
		if (food->GetOwner() == nullptr)
		{
			ClaimFood(food);
			return;
		}
	}
}
