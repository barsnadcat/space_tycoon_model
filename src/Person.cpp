#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Building.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Space* parent = GetParent();
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
			parent->AddPerson(std::make_shared<Person>(30000, 0));
		}
	}
}

void Person::Scavenge()
{
	Space* parent = GetParent();
	assert(parent);

	for (BuildingSP& building : parent->GetBuildings())
	{
		if (building->GetOwner() == nullptr)
		{
			ClaimBuilding(building);
			return;
		}
	}

	for (FoodSP& food : parent->GetFoods())
	{
		if (food->GetOwner() == nullptr)
		{
			ClaimFood(food);
			return;
		}
	}
}
