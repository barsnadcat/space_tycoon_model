#include <Person.h>

#include <UpdateContext.h>
#include <Entity.h>
#include <Owner.h>
#include <Space.h>
#include <Farm.h>
#include <Food.h>
#include <Property.h>

const int32_t kMaxEnergy = 200;

std::shared_ptr<Person> ConstructPerson(uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences)
{
	auto person = std::make_shared<Person>(energy, preferences);
	person->mEntity = std::make_unique<Entity>(health);
	person->mOwner = std::make_unique<Owner>(person);
	return person;
}

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
			return mOwner->GetOwned(productId);
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
					auto farm = ConstructFarm(5000);
					space->AddBuilding(farm);
					mOwner->ClaimFarm(farm);
				}
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					auto food = ConstructFood(100);
					space->AddFood(food);
					mOwner->ClaimFood(food);
				}
			}
		}
	}
}

void Person::OnObjectUpdated(UpdateContext& uc)
{
	if (ObjectSP space = mEntity->GetParent())
	{
		Produce(uc, space->mSpace.get(), GetBestProduction(uc));
	}

    // Eat
	ObjectSP food = mOwner->GetMyNearFood();
	if (food)
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + food->mFood->GetEnergy());
		food->mEntity->SetMaxHealth(0);
	}

    // Expend energy or hunger damage
	if (mEnergy == 0)
	{
		mEntity->DamageHealth(1);
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
		space->AddPerson(ConstructPerson(30000, 100, Mutate(uc, mPreferences)));
	}
}

void Person::Scavenge(Space* space)
{
	for (ObjectSP& farm : space->GetFarms())
	{
		if (farm->mProperty->GetOwner() == nullptr)
		{
			mOwner->ClaimFarm(farm);
			return;
		}
	}

	for (ObjectSP& food : space->GetFoods())
	{
		if (food->mProperty->GetOwner() == nullptr)
		{
			mOwner->ClaimFood(food);
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
