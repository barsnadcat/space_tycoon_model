#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Farm.h>

const int32_t kMaxEnergy = 200;

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float> preferences)
{
	if (!preferences.empty())
	{
		auto it = preferences.begin();
		auto sizeDist = std::uniform_int_distribution<size_t>(0, preferences.size() - 1);
		auto floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
		std::advance(it, sizeDist(uc.mRandomEngine));
		it->second = (it->second + floatDist(uc.mRandomEngine)) / 2.0f;
	}
	return preferences;
}

std::map<ProductId, float> RandomPreferences(UpdateContext& uc)
{
	std::map<ProductId, float> preferences;
	auto floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
	preferences[kFoodId] = floatDist(uc.mRandomEngine);
	preferences[kFarmId] = floatDist(uc.mRandomEngine);
	preferences[kEffortId] = floatDist(uc.mRandomEngine);
	preferences[kFamilyMemberId] = floatDist(uc.mRandomEngine);
	preferences[kRandomProductId] = floatDist(uc.mRandomEngine);
	return preferences;
}

int32_t Person::GetPersonOwned(ProductId productId) const
{
	switch (productId)
	{
	case kEffortId:
		return mEnergy;
	case kFamilyMemberId:
		return mChildren;
	case kFoodId:
	case kRandomProductId:
		return GetFoods().size();
	default:
		return 0;
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

void Person::Produce(UpdateContext& uc, ProductionId productionId)
{
	if (productionId == kInvalidId)
	{
		return;
	}

	if (productionId == kScavengeId)
	{
		Scavenge();
		return;
	}

	if (productionId == kReproductionId)
	{
		Reproduce(uc);
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
                // Number greater than 1 does not make sens
                // You building where you are - i.e. on that land plot
                // To do: check if you own that land
                // Actually enforcing presence of pointer will be really helpfull...
				Building* pBuilding = GetBuilding();
				if (pBuilding)
				{
					Land* pLand = pBuilding->GetLand();
					if (!pLand->GetBuilding())
					{
						Farm* farm = new Farm(this, 5000, 1);
						pLand->SetBuilding(BuildingPtr(farm));
					}
				}
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					AddItem(kFoodId, ItemPtr(new Food(this, 100)));
				}
			}
		}
	}
}

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Produce(uc, GetBestProduction(uc));

    // Eat
	if (FoodPtr food = Take<Food>(kFoodId))
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + food->GetEnergy());
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

void Person::Reproduce(UpdateContext& uc)
{
	Building* building = GetBuilding();
	if (mEnergy > 100 && building)
	{
		mEnergy = 0;
		mChildren++;
		building->AddOwner(std::make_unique<Person>(this, 30000, 100, Mutate(uc, mPreferences)));
	}
}

void Person::Scavenge()
{
	Building* building = GetBuilding();
	if (!building)
	{
		return;
	}
	Land* land = building->GetLand();
	if (!land)
	{
		return;
	}
	Space* space = land->GetSpace();
	if (!space)
	{
		return;
	}
    // move to random space
	size_t neighbor = space->GetNeighbour(land->GetIndex());
	Land* pTargetLand = space->GetLand(neighbor);
	building->RemoveOwner(this);
	pTargetLand->GetNullBuilding().AddOwner(std::unique_ptr<Owner>(this));

    // Ambiguous situtation, where do owner goes in which building?

    // Try claim building, then enter it, other wise go to nothing

    // Try claim stuff in building

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
