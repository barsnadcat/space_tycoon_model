#pragma once

#include <EntitiesDeclarations.h>
#include <Property.h>

#include <cassert>
#include <memory>
#include <vector>
#include <map>


struct UpdateContext;
using People = std::vector<PersonSP>;

class Space
{
public:
	virtual ~Space() {}
	void Update(UpdateContext& uc);

	void AddPerson(PersonSP p);
	People& GetPeople() { return mPeople; }

	void AddFood(FoodSP p);
	EntitySPs& GetFoods() { return mProducts[kFoodId]; }

	void AddBuilding(FarmSP p);
	EntitySPs& GetFarms() { return mProducts[kFarmId]; }

	void MoveTo(Space& space);

private:
	template<typename T>
	void DeleteEntities(std::vector<std::shared_ptr<T>>& container);
	virtual void OnSpaceUpdated(UpdateContext& uc){}

private:
	std::map<ProductId, EntitySPs> mProducts;
	People mPeople;
};
