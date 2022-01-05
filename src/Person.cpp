#include <Person.h>

#include <Settlement.h>
#include <Food.h>
#include <Farm.h>
#include <Land.h>

const int32_t kMaxEnergy = 200;

Person::Person(Land* land, uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences): Entity(land, health, 1)
	, mEnergy(energy), mPreferences(preferences)
{
	assert(land);
	mLand = land;
	land->AddPerson(this);
}

Person::~Person()
{
	if (mLand)
	{
		mLand->RemovePerson(this);
	}

	for (auto p : mFoods)
	{
		p->SetPerson(nullptr);
	}

	if (mFarm)
	{
		mFarm->SetPerson(nullptr);
	}
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
	switch (productId)
	{
	case kEffortId:
		return mEnergy;
	case kFamilyMemberId:
		return mChildren;
	case kFarmId:
		return mFarm ? 1 : 0;
	case kFoodId:
		return mFoods.size();
	case kRandomProductId:
		return mFoods.size() + mEnergy;
	case kLandId:
		return mLand->GetFarm() == nullptr ? 1 : 0;
	default:
		return 0;
	}
}

float Person::GetMarginalUtility(UpdateContext& uc, ProductId pId, int32_t number) const
{
	return GetPersonalPreference(pId) * uc.mObjectiveUtilities[pId].GetMarginalUtility(GetPersonOwned(pId), number);
}

bool Person::CanDoProduction(UpdateContext& uc, ProductionId productionId) const
{
	const std::vector<ProductionConfig>& v = uc.mProductions[productionId];
	for (const ProductionConfig& pc : v)
	{
		if (pc.number + GetPersonOwned(pc.productId) < 0)
		{
			return false;
		}
	}
	return true;
}

float Person::GetProductionValue(UpdateContext& uc, ProductionId productionId) const
{
	float res = 0;
	const std::vector<ProductionConfig>& v = uc.mProductions[productionId];
	for (const ProductionConfig& pc : v)
	{
		if (!pc.tool)
		{
			res += GetMarginalUtility(uc, pc.productId, pc.number);
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
				assert(mLand->GetFarm() == nullptr);
				assert(mFarm == nullptr);
				assert(it.number > 0);
				AddFarm(new Farm(mLand, 30000));
			}
			if (it.productId == kFoodId)
			{
				for (int32_t i = 0; i < it.number; ++i)
				{
					AddFood(new Food(mLand, 100));
				}
			}
		}
	}
}

void Person::OnEntityUpdated(UpdateContext& uc)
{
	Produce(uc, GetBestProduction(uc));

    // Eat
	if (!mFoods.empty())
	{
		Food* food = mFoods.back();
		mFoods.pop_back();
		food->SetPerson(nullptr);
		mEnergy = std::min(kMaxEnergy, mEnergy + food->GetEnergy());
		delete food;
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
	mEnergy = 0;
	mChildren++;
	new Person(mLand, 30000, 100, Mutate(uc, mPreferences));
}

void Person::Scavenge()
{
    // move to next land
	Land* newLand = mLand->GetSettlement()->GetNeighbour(mLand);
	if (newLand != mLand)
	{
        // Disown everything
		for (Food* p : mFoods)
		{
			p->SetPerson(nullptr);
		}
		mFoods.clear();

		if (mFarm)
		{
			RemoveFarm(mFarm);
		}
        // Move
		mLand->RemovePerson(this);
		newLand->AddPerson(this);
		mLand = newLand;
	}

    // Search for building
	Farm* farm = newLand->GetFarm();
	if (farm && farm->GetPerson() == nullptr)
	{
		AddFarm(farm);
		return;
	}
	for (Food* food : newLand->GetFoods())
	{
		if (food->GetPerson() == nullptr)
		{
			AddFood(food);
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

void Person::AddFood(Food* p)
{
	assert(p);
	p->SetPerson(this);
	mFoods.push_back(p);
}

void Person::RemoveFood(Food* p)
{
	assert(p);
	p->SetPerson(nullptr);
	mFoods.erase(std::remove(mFoods.begin(), mFoods.end(), p), mFoods.end());
}

void Person::AddFarm(Farm* p)
{
	assert(mFarm == nullptr);
	assert(p);
	p->SetPerson(this);
	mFarm = p;
}

void Person::RemoveFarm(Farm* p)
{
	assert(p);
	assert(p == mFarm);
	p->SetPerson(nullptr);
	mFarm = nullptr;
}
