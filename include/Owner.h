#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <memory>
#include <map>
#include <cassert>

class Owner
{
public:
	Owner(ObjectSP thisObject): mThisObject(thisObject)
	{
		assert(thisObject);
	}
	void ClaimFood(ObjectSP food);
	void ClaimFarm(ObjectSP building);
	ObjectWPs& GetMyFoods() { return mEntities[kFoodId]; }
	ObjectSP GetMyNearFood();
	int32_t GetOwned(ProductId productId) const;

private:
	ObjectWP mThisObject;
	std::map<ProductId, ObjectWPs> mEntities;
};
