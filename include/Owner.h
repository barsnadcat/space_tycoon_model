#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <memory>
#include <map>

class Owner
{
public:
	Owner(Object& thisObject): mThisObject(thisObject)
	{
	}
	void ClaimFood(ObjectSP food);
	void ClaimFarm(ObjectSP building);
	ObjectWPs& GetMyFoods() { return mEntities[kFoodId]; }
	ObjectSP GetMyNearFood();
	int32_t GetOwned(ProductId productId) const;

private:
	Object& mThisObject;
	std::map<ProductId, ObjectWPs> mEntities;
};
