#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Farm.h>

const int32_t kMaxEnergy = 200;

float Person::GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const
{
	int32_t owned = 0;
	if (productId == kEffortId)
	{
		owned = mEnergy;
	}
	else
	{
		if (kReproductionId)
		{
			owned = mChildren;
		}
		else
		{
			owned = GetOwned(productId);
		}
	}

	return GetPersonalPreference(productId) * uc.mObjectiveUtilities[productId].GetMarginalUtility(owned, number);
}

float Person::GetProductionValue(UpdateContext& uc, ProductionId productionId) const
{
	float res = 0;
	for (auto input : uc.mProductions[productionId])
	{
		res += GetMarginalUtility(uc, input.first, input.second);
	}
	return res;
}

ProductionId Person::GetBestProduction(UpdateContext& uc) const
{
	float bestProductionValue = 0;
	ProductionId bestProductionId = kInvalidId;
	for (const auto& p : uc.mProductions)
	{
        //    if (CanDoProduction(prouctionSettings))
		float productionValue = GetProductionValue(uc, p.first);
		if (productionValue > bestProductionValue)
		{
			bestProductionId = p.first;
			bestProductionValue = productionValue;
		}
	}
	return bestProductionId;
}

void Person::Produce(UpdateContext& uc, Space* space, ProductionId productionId)
{
	if (productionId == kInvalidId)
	{
		return;
	}

	if (productionId == kScavengeId)
	{
		Scavenge(space);
		return;
	}

	if (productionId == kReproductionId)
	{
		Reproduce(uc, space);
		return;
	}

	for (auto it : uc.mProductions[productionId])
	{
		if (it.first == kEffortId)
		{
			mEnergy += it.second;
		}
		if (it.first == kFarmId)
		{
			for (int32_t i = 0; i < it.second; ++i)
			{
				auto farm = std::make_shared<Farm>(5000);
				space->AddBuilding(farm);
				ClaimFarm(farm);
			}
		}
		if (it.first == kFoodId)
		{
			for (int32_t i = 0; i < it.second; ++i)
			{
				auto food = std::make_shared<Food>(100);
				space->AddFood(food);
				ClaimFood(food);
			}
		}
	}
}

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	if (Space* space = GetParent())
	{
		Produce(uc, space, GetBestProduction(uc));
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
}

void Person::Reproduce(UpdateContext& uc, Space* space)
{
	if (mEnergy > 100)
	{
		mEnergy = 0;
		mChildren++;
		space->AddPerson(std::make_shared<Person>(30000, 0, mPreferences));
	}
}

void Person::Scavenge(Space* space)
{
	for (EntitySP& farm : space->GetFarms())
	{
		if (farm->GetOwner() == nullptr)
		{
			ClaimFarm(farm);
			return;
		}
	}

	for (EntitySP& food : space->GetFoods())
	{
		if (food->GetOwner() == nullptr)
		{
			ClaimFood(food);
			return;
		}
	}
}

float Person::GetPersonalPreference(ProductId productId) const
{
	auto it = mPreferences.find(productId);
	if (it != mPreferences.end())
	{
		return it->second;
	}
	else
	{
		return 0.5f;
	}
	
}
