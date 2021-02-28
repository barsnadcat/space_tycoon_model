#include <Person.h>

#include <UpdateContext.h>
#include <Entity.h>
#include <Owner.h>
#include <Space.h>
#include <Farm.h>
#include <Food.h>
#include <Property.h>

const int32_t kMaxEnergy = 200;

ObjectSP ConstructPerson(uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences)
{
	auto person = std::make_shared<Object>();
	person->person = std::make_unique<Person>(*person, energy, preferences);
	person->entity = std::make_unique<Entity>(health);
	person->owner = std::make_unique<Owner>(*person);
	return person;
}

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float> preferences)
{
	if (!preferences.empty())
	{
		auto it = preferences.begin();
		auto sizeDist = std::uniform_int_distribution<size_t>(0, preferences.size() - 1);
		auto floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
		std::advance(it, sizeDist(uc.randomEngine));
		it->second = (it->second + floatDist(uc.randomEngine)) / 2.0f;
	}
	return preferences;
}

std::map<ProductId, float> RandomPreferences(UpdateContext& uc)
{
	std::map<ProductId, float> preferences;
	auto floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
	preferences[kFoodId] = floatDist(uc.randomEngine);
	preferences[kFarmId] = floatDist(uc.randomEngine);
	preferences[kEffortId] = floatDist(uc.randomEngine);
	preferences[kFamilyMemberId] = floatDist(uc.randomEngine);
	preferences[kRandomProductId] = floatDist(uc.randomEngine);
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
			return mThisObject.owner->GetOwned(productId);
		}
	}
}

float Person::GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const
{
	return GetPersonalPreference(productId) * uc.objectiveUtilities[productId].GetMarginalUtility(GetPersonOwned(productId), number);
}

bool Person::CanDoProduction(UpdateContext& uc, ProductionId productionId) const
{
	for (auto it : uc.productions[productionId])
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
	for (auto it : uc.productions[productionId])
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
	for (const auto& p : uc.productions)
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

	for (auto it : uc.productions[productionId])
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
					mThisObject.owner->ClaimFarm(farm);
				}
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					auto food = ConstructFood(100);
					space->AddFood(food);
					mThisObject.owner->ClaimFood(food);
				}
			}
		}
	}
}

void Person::Update(UpdateContext& uc)
{
	if (ObjectSP space = mThisObject.entity->GetParent())
	{
		Produce(uc, space->space.get(), GetBestProduction(uc));
	}

    // Eat
	ObjectSP food = mThisObject.owner->GetMyNearFood();
	if (food)
	{
		mEnergy = std::min(kMaxEnergy, mEnergy + food->food->GetEnergy());
		food->entity->SetMaxHealth(0);
	}

    // Expend energy or hunger damage
	if (mEnergy == 0)
	{
		mThisObject.entity->DamageHealth(1);
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
		if (farm->property->GetOwner() == nullptr)
		{
			mThisObject.owner->ClaimFarm(farm);
			return;
		}
	}

	for (ObjectSP& food : space->GetFoods())
	{
		if (food->property->GetOwner() == nullptr)
		{
			mThisObject.owner->ClaimFood(food);
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
