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

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Space* parent = GetParent();

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

	if (bestProductionId == kScavengeId)
	{
		Scavenge();
	}
	else
	{
		if (bestProductionId == kReproductionId)
		{
			Reproduce(uc);
		}
		else
		{
			Produce(uc, bestProductionId);
		}
	}


    // If person does not know how to use tool - its personal modifer for its utility should be 0. It still may hold 'resell' value

    // Problem: productionSettings, and objectiveUtiltiy objects are where?
    //  1 - on person
    //  2 - on context
    // Problem: objectiveUtility maybe has to be person specific, place specific or global?
    //  - Leave 0-1 multiplier on person, and move all arbitrary values to objective utility
    // Porblem: reproduction doesn not have any thing that can be tracked as "owned", nor does scavenging
    // For savenging we can calculate total owned.
    // For reproduction we can have separate counter in owner class.
    // Problem: Where is verification that we have necessary ingredient for production?
    //  1 - Inside GetValue - meh
    //  2 - Separate function


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

void Person::Produce(UpdateContext& uc, ProductionId productionId)
{
	Space* parent = GetParent();
	assert(parent);

	for (auto it: uc.mProductions[productionId])
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
				parent->AddBuilding(farm);
				ClaimFarm(farm);
			}
		}
		if (it.first == kFoodId)				
		{
			for (int32_t i = 0; i < it.second; ++i)
			{
				auto food = std::make_shared<Food>(100);
				parent->AddFood(food);
				ClaimFood(food);
			}
		}		
	}
}

void Person::Reproduce(UpdateContext& uc)
{
	Space* parent = GetParent();
	assert(parent);

	if (parent && mEnergy > 100)
	{
		std::bernoulli_distribution distribution(0.25);
		if (distribution(uc.mRandomEngine))
		{
			mEnergy = 0;
			mChildren++;
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
