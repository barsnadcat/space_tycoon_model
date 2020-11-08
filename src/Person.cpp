#include <Person.h>

#include <UpdateContext.h>
#include <Space.h>
#include <Farm.h>

const int kMaxEnergy = 200;

void Person::OnOwnerUpdated(UpdateContext& uc)
{
	Space* parent = GetParent();


	// class ObjectiveUtility
	//     ObjectiveUtility(optimal quantity, usless quatity);
	//     float GetMarginalUtility(number, owned) const; // never returns higher that 1.0

	// float Person::GetMarginalUtility(productId, number) const
	// {
    //     return mPersonalPreference[productId] * mObjectiveUtilities[productId].GetMarginalUtility(number, GetOwned(productId));
	// }

	// Problems currently:
	// Scavenging priority is rather suboptimal to derive from its possible outputs - there will be to many...
	// Procreation - sex and child birth is an production too, and it its outupu is a person. 
	// Well, we can have utility function for that, but you do not own people! Rather you have them in your "family"
	// Any way, its outside of model 1 scope.
	// So how do we handle this to options?
	// They have to be in same list as other productions, but have to have different code for them.
	// Production object + virtual functions?
	// 


	// BuildOwnedGoodsValuation
	// for product in all product types:
	//    values[product] = 1/owned * like
	//    so here is the question, we need funtion that ouptupts utility, based on quantity of item and preference of person
	//    function should rise, than fall. 
	// But how fast it should raise and fall, at what point it starts to fall, what is absoulute values are can 
	// depend both on item and person! I.e. absolute value of farm should be higer that apples. Second
	// Our examples: food should start getting less valueble as soon as you can not eat it before it spoils
	// First farm should be very valuable, but second one almost worthless
	// Energy each next energy should be valued a lot more, and since there is hard cap on energy you can own, it does not fall
	// Hypotetical examples of personal preferences:
	// Somebody will like to hoard apples, i.e. his function is scaled along quantity axis
	// Somebody will like food more that farm, i.e. his function is scaled along utility axis
	// But there is no point in scaling utility of farm along quantity axis, and same for energy... sort of
	// Ok, goods utility is objective utility. This can be 0, optimal quantity of good, and unmanagable ammount of goods, so
	// Another idea, that this parabola has maximum y at 1. Then person just scales y by multiplying it. By peference number.

	// Well well, we actually need marginal utility, so we need current quantity of items, and new quantity of items, then their utility difference.
	// What if we have 0 farms, and build outpus 2 farms, so we end up with 2 farms, which are usless. Which is not true, marginal utility of second farm is not -1
	// it is 0.1 or some thing, i.e it is nice to have one if previous one expires. 
	// Currently, in game there is no mechanics that punishes owing too much, and we probably do not need it.
	// Marginal utility has to be 0 at some point, and then go negative.
	// Should total utility reach 0?
	// In real world it objectively can, but subjectively... people will not refuse of an asteroid of gold... Or actually they would.

	// What about using marginal utility function instead?
	// Using linear functions seems a lot simpler.

	// If person does not know how to use tool - its personal modifer for its utility should be 0. It still may hold 'resell' value
	

    // goods valuation = BuildOwnedGoodsValuation
    // GetBestProduction
    // max value = 0;
    // best production = none;
    // for all productions:
	//  currValue = GetProductionValuation(goods valuation)
    //  if curr value > max value:
    //     max value = curr value
    //     best activity = currActivity
	// scavenge valuation = GetScavengeValuation(goods valuation)
	// if bets value > scavenge valuation
	//    return best production
	// else
	//    return scavenging

	// GetProductionValuation
    //  n = get how much of output owned
    //  m = how muc of output is produced by activity
    //  cur value = m/n * mActivityPreference[currActivity]

    // We need production id and product id types
    // We need production parameters:
    // Ie. Production1
	// Energy expense - 10
    // Tool - Product2
    // Outpout - quantity? chance? both? of Product3, quantity of Product4
    // Scavenging is production too
	// For scavenging we will have loop for all possible things here, which is suboptimal!
	// But like if you have a lot of stuff, scavenging is not really necessary.
	// Ok, what about combining primary production selection pass with calculating value of scavenging!
	// Like average value? Min value? Min value would not work. 
	// Idea: use unit tests. Function that outputs production valuation.
	// We should have different value for all 3 productions depending on persons
	//  - owned energy, amount of food and farms 
	//  - valuation of energy, food and farms
	// Unit test can not cover scavenging if scavenging is calculated in special way.
	// Well we can put test higher - Function that outputs selected activity
	// More over, we need function that outputs product valuation, for trading later.


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
