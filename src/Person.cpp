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

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Space* parent = GetParent();

    // We need production id and product id types

    // More over, we need function that outputs product valuation, for trading later.
    // Ok, goods utility is objective utility. This can be 0, optimal quantity of good, and unmanagable ammount of goods, so
    // Another idea, that this parabola has maximum y at 1. Then person just scales y by multiplying it. By peference number.

    // class ObjectiveUtility
    //     ObjectiveUtility(optimal quantity, usless quatity);
    //     float GetMarginalUtility(number, owned) const; // never returns higher that 1.0

    // float Person::GetMarginalUtility(productId, number) const
    // {
    //     return mPersonalPreference[productId] * mObjectiveUtilities[productId].GetMarginalUtility(number, GetOwned(productId));
    // }

    // Scavenging priority is rather suboptimal to derive from its possible outputs - there will be to many...
    // Procreation - sex and child birth is an production too, and it its outupu is a person.
    // Well, we can have utility function for that, but you do not own people! Rather you have them in your "family"
    // Any way, its outside of model 1 scope.
    // Hm we can have dummy productIds for those productions "Family" and "Luck". Energy is special product id any way...
    // So that all utility code will be same. Still, we need custom code to execute this productions, i.e. hardcode

    //     float Person::GetProductionValue(productionSettings)
    //     {
    //         float res = 0;
    //         for (input: productionSettings.inputs)
    //             res -= GetMaringalUtility(input.product, input.quantity)
    //         for (output: productionSettings.outputs)
    //             res += GetMaringalUtility(output.product, output.quantity)
    //         return res
    //     }
    //
    // Person::Update
    // maxValue = 0;
    // bestProductionId = InvalidProductionId;
    // for productionSettings: productionSttings:
    //    if (CanDoProduction(prouctionSettings))
    //       currValue = GetProductionValue(productionSettings)
    //       if currValue > maxValue:
    //           maxValue = currValue
    //           bestProductionId = currProductionId
    //
    // switch betstProductionId
    // case kScavengingId:
    //     Scavenge();
    //     break;
    // case kProcreate:
    //     Procrate();
    //     break;
    //  default:
    //     Produce(productionId);
    //
    // PersonProduce(productionId)
    //  for input: productionSettings.inputs
    //     Consume(input.prouctId, input.quantity);
    //  for output: productionSettings.ouputs
    //     Create(otput.productId, output.quantity);

    // If person does not know how to use tool - its personal modifer for its utility should be 0. It still may hold 'resell' value

    // Problem: productionSettings, and objectiveUtiltiy objects are where?
    //  1 - on person
    //  2 - on context
    // Problem: objectiveUtility maybe has to be person specific, place specific or global?
    //  - Leave 0-1 multiplier on person, and move all arbitrary values to objective utility
    // Problem: Where is verification that we have necessary ingredient for production?
    //  1 - Inside GetValue - meh
    //  2 - Separate function
    // Porblem: reproduction doesn not have any thing that can be tracked as "owned", nor does scavenging
    // For savenging we can calculate total owned.
    // For reproduction we can have separate counter in owner class.

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
