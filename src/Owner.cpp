#include <Owner.h>
#include <Food.h>
#include <Farm.h>

void Owner::ClaimFood(EntitySP food)
{
	food->SetOwner(std::static_pointer_cast<Owner>(shared_from_this()));
	mEntities[kFoodId].push_back(food);
}

void Owner::ClaimFarm(EntitySP building)
{
	building->SetOwner(std::static_pointer_cast<Owner>(shared_from_this()));
	mEntities[kFarmId].push_back(building);
}

FoodSP Owner::GetMyNearFood()
{
	for (auto it = mEntities[kFoodId].begin(); it != mEntities[kFoodId].end();)
	{
		EntitySP food = (*it).lock();
		if (food)
		{
			if (food->GetParent() == GetParent() && food->GetHealth() > 0)
			{
				return std::static_pointer_cast<Food>(food);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it = mEntities[kFoodId].erase(it);
		}
	}
	return nullptr;
}

int Owner::GetOwned(ProductId productId) const
{
	if(productId == kRandomProductId)
	{
		int total = 0;
		for (const auto& p: mEntities)
		{
			total += p.second.size();
		}
	}
	else
	{
		const auto& it = mEntities.find(productId);
		if (it == mEntities.end())
		{
			return 0;
		}
		else
		{
			return it->second.size();
		}
	}
}
