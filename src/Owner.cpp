#include <Owner.h>

#include <Property.h>
#include <Space.h>
#include <Entity.h>

void Owner::Claim(ProductId productId, ObjectSP object)
{
	object->property->SetOwner(mThisObject.shared_from_this());
	mProperty[productId].push_back(object);
}

int32_t Owner::GetOwnedCount(ProductId productId) const
{
	if (productId == kRandomProductId)
	{
		int32_t total = 0;
		for (const auto& p : mProperty)
		{
			total += p.second.size();
		}
		return total;
	}
	else
	{
		const auto& it = mProperty.find(productId);
		if (it == mProperty.end())
		{
			return 0;
		}
		else
		{
			return it->second.size();
		}
	}
}

ObjectSP Owner::GetMyNearFood()
{
	for (auto it = mProperty[kFoodId].begin(); it != mProperty[kFoodId].end();)
	{
		ObjectSP food = (*it).lock();
		if (food)
		{
			if (food->entity->GetParent() == mThisObject.entity->GetParent() && food->entity->GetHealth() > 0)
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
			it = mProperty[kFoodId].erase(it);
		}
	}
	return nullptr;
}
