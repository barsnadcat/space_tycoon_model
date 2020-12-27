#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Farm.h>

const int32_t kMaxEnergy = 200;

int32_t Person::GetPersonOwned(ProductId productId) const
{
	if (productId == kEffortId)
	{
		return mEnergy;
	}
	else
	{
		if (productId == kReproductionId)
		{
			return mChildren;
		}
		else
		{
			return GetOwned(productId);
		}
	}
}

float Person::GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const
{
	return GetPersonalPreference(productId) * uc.mObjectiveUtilities[productId].GetMarginalUtility(GetPersonOwned(productId), number);
}

bool Person::CanDoProduction(UpdateContext& uc, ProductionId productionId) const
{
	for (auto it : uc.mProductions[productionId])
	{
		if (it.number + GetPersonOwned(it.productId) < 0)
		{
			return false;
		}
	}
	return true;
}

float Person::GetProductionValue(UpdateContext& uc, ProductionId productionId) const
{
	float res = 0;
	for (auto it : uc.mProductions[productionId])
	{
		if (!it.tool)
		{
			res += GetMarginalUtility(uc, it.productId, it.number);
		}
	}
	return res;
}

ProductionId Person::GetBestProduction(UpdateContext& uc) const
{
	float bestProductionValue = 0;
	ProductionId bestProductionId = kInvalidId;
	for (const auto& p : uc.mProductions)
	{
		if (CanDoProduction(uc, p.first))
		{
			float productionValue = GetProductionValue(uc, p.first);
			if (productionValue > bestProductionValue)
			{
				bestProductionId = p.first;
				bestProductionValue = productionValue;
			}
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
		if (!it.tool)
		{
			if (it.productId == kEffortId)
			{
				mEnergy += it.number;
			}
			if (it.productId == kFarmId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					auto farm = std::make_shared<Farm>(5000);
					space->AddBuilding(farm);
					ClaimFarm(farm);
				}
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					auto food = std::make_shared<Food>(100);
					space->AddFood(food);
					ClaimFood(food);
				}
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
