#include <Person.h>

#include <UpdateContext.h>
#include <Entity.h>
#include <Owner.h>
#include <Space.h>
#include <Farm.h>
#include <Food.h>
#include <Property.h>

const int32_t kMaxEnergy = 200;

ObjectSP ConstructPerson(uint32_t health, int32_t energy, const std::map<ObjectId, float>& preferences)
{
	auto person = std::make_shared<Object>(kPersonId);
	person->person = std::make_unique<Person>(*person, energy, preferences);
	person->entity = std::make_unique<Entity>(health);
	person->owner = std::make_unique<Owner>(*person);
	return person;
}

std::map<ObjectId, float> Mutate(UpdateContext& uc, std::map<ObjectId, float> preferences)
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

std::map<ObjectId, float> RandomPreferences(UpdateContext& uc)
{
	std::map<ObjectId, float> preferences;
	auto floatDist = std::uniform_real_distribution<float>(0.0f, 1.0f);
	preferences[kFoodId] = floatDist(uc.randomEngine);
	preferences[kFarmId] = floatDist(uc.randomEngine);
	preferences[kEffortId] = floatDist(uc.randomEngine);
	preferences[kPersonId] = floatDist(uc.randomEngine);
	preferences[kRandomProductId] = floatDist(uc.randomEngine);
	return preferences;
}

int32_t Person::GetPersonOwned(ObjectId productId) const
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
			return mThisObject.owner->GetOwnedCount(productId);
		}
	}
}

float Person::GetMarginalUtility(UpdateContext& uc, ObjectId productId, int32_t number) const
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

void Person::Produce(UpdateContext& uc, Object& workSpace, ProductionId productionId)
{
	if (productionId == kInvalidId)
	{
		return;
	}

	if (productionId == kScavengeId)
	{
		Scavenge(workSpace);
		return;
	}

	if (productionId == kReproductionId)
	{
		Reproduce(uc, workSpace);
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
					workSpace.space->Add(farm);
					mThisObject.owner->Claim(farm);
				}
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					auto food = ConstructFood(100);
					workSpace.space->Add(food);
					mThisObject.owner->Claim(food);
				}
			}
		}
	}
}

void Person::Update(UpdateContext& uc)
{
	if (ObjectSP workSpace = mThisObject.entity->GetParent())
	{
		Produce(uc, *workSpace, GetBestProduction(uc));
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

void Person::Reproduce(UpdateContext& uc, Object& workSpace)
{
	if (mEnergy > 100)
	{
		mEnergy = 0;
		mChildren++;
		workSpace.space->Add(ConstructPerson(30000, 100, Mutate(uc, mPreferences)));
	}
}

void Person::Scavenge(Object& workSpace)
{
	for (ObjectSP& farm : workSpace.space->Get(kFarmId))
	{
		if (farm->property->GetOwner() == nullptr)
		{
			mThisObject.owner->Claim(farm);
			return;
		}
	}

	for (ObjectSP& food : workSpace.space->Get(kFoodId))
	{
		if (food->property->GetOwner() == nullptr)
		{
			mThisObject.owner->Claim(food);
			return;
		}
	}
}

float Person::GetPersonalPreference(ObjectId productId) const
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
