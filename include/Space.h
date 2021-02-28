#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <cassert>
#include <memory>
#include <vector>
#include <map>

struct UpdateContext;

class Space
{
public:
	Space(ObjectSP thisObject): mThisObject(thisObject)
	{
		assert(thisObject);
	}
	void Update(UpdateContext& uc);

	void AddPerson(ObjectSP p);
	ObjectSPs& GetPeople() { return mPeople; }

	void AddFood(ObjectSP p);
	ObjectSPs& GetFoods() { return mProducts[kFoodId]; }

	void AddBuilding(ObjectSP p);
	ObjectSPs& GetFarms() { return mProducts[kFarmId]; }

	void MoveTo(ObjectSP space);

private:
	ObjectWP mThisObject;
	std::map<ProductId, ObjectSPs> mProducts;
	ObjectSPs mPeople;
};
