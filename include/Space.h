#pragma once

#include <EntitiesDeclarations.h>
#include <Property.h>

#include <cassert>
#include <memory>
#include <vector>


struct UpdateContext;
using Foods = std::vector<FoodSP>;
using People = std::vector<PersonSP>;
using Farms = std::vector<FarmSP>;

class Space: public Property
{
public:
	virtual ~Space() {}
	void Update(UpdateContext& uc);

	void AddPerson(PersonSP p);
	People& GetPeople() { return mPeople; }

	void AddFood(FoodSP p);
	Foods& GetFoods() { return mFoods; }

	void AddBuilding(FarmSP p);
	Farms& GetFarms() { return mFarms; }

	void MoveTo(Space& space);

private:
	template<typename T>
	void DeleteEntities(std::vector<std::shared_ptr<T>>& container);
	virtual void OnSpaceUpdated(UpdateContext& uc){}

private:
	Foods mFoods;
	People mPeople;
	Farms mFarms;
};
