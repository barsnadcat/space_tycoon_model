#pragma once

#include <Property.h>

#include <cassert>
#include <memory>
#include <vector>

class Entity;
class Food;
class Person;
class Building;
struct UpdateContext;

using FoodPtr = std::shared_ptr<Food>;
using Foods = std::vector<FoodPtr>;
using PersonPtr = std::shared_ptr<Person>;
using People = std::vector<PersonPtr>;
using BuildingPtr = std::shared_ptr<Building>;
using Buildings = std::vector<BuildingPtr>;

class Space: public Property
{
public:
	virtual ~Space() {}
	void Update(UpdateContext& uc);

	void AddPerson(PersonPtr p);
	People& GetPeople() { return mPeople; }

	void AddFood(FoodPtr p);
	Foods& GetFoods() { return mFoods; }

	void AddBuilding(BuildingPtr p);
	Buildings& GetBuildings() { return mBuildings; }

	void MoveTo(Space& space);

private:
	template<typename T>
	void DeleteEntities(std::vector<std::shared_ptr<T>>& container);
	virtual void OnSpaceUpdated(UpdateContext& uc){}

private:
	Foods mFoods;
	People mPeople;
	Buildings mBuildings;
};
