#include <Owner.h>

#include <Property.h>
#include <Space.h>
#include <Entity.h>

void Owner::ClaimFood(ObjectSP food)
{
	food->mProperty->SetOwner(mThisObject.lock());
	mEntities[kFoodId].push_back(food);
}

void Owner::ClaimFarm(ObjectSP farm)
{
	farm->mProperty->SetOwner(mThisObject.lock());
	mEntities[kFarmId].push_back(farm);
}

ObjectSP Owner::GetMyNearFood()
{
	for (auto it = mEntities[kFoodId].begin(); it != mEntities[kFoodId].end();)
	{
		ObjectSP food = (*it).lock();
		if (food)
		{
			if (food->mEntity->GetParent() == mThisObject.lock()->mEntity->GetParent() && food->mEntity->GetHealth() > 0)
			{
				return food;
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

int32_t Owner::GetOwned(ProductId productId) const
{
	if (productId == kRandomProductId)
	{
		int32_t total = 0;
		for (const auto& p : mEntities)
		{
			total += p.second.size();
		}
		return total;
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
