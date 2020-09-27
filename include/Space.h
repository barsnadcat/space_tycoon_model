#pragma once

#include <cassert>
#include <memory>
#include <vector>

class Entity;
class Food;
class Person;
class Building;
struct UpdateContext;

using FoodPtr = std::unique_ptr<Food>;
using Foods = std::vector<FoodPtr>;
using PersonPtr = std::unique_ptr<Person>;
using People = std::vector<PersonPtr>;
using BuildingPtr = std::unique_ptr<Building>;
using Buildings = std::vector<BuildingPtr>;

class Space
{
public:
	virtual ~Space() {}
	Space* GetParent() { return mParent; }
	void Update(UpdateContext& uc);

	void AddPerson(PersonPtr p);
	People& GetPeople() { return mPeople; }

	void AddFood(FoodPtr p);
	Foods& GetFoods() { return mFoods; }

	void AddBuilding(BuildingPtr p);
	Buildings& GetBuildings() { return mBuildings; }

	void MoveTo(Space& space);

private:
	void SetParent(Space* space) { mParent = space; }
	template<typename T>
	void DeleteEntities(std::vector<std::unique_ptr<T>>& container);
	virtual void OnSpaceUpdated(UpdateContext& uc){}

private:
	Space* mParent = nullptr;
	Foods mFoods;
	People mPeople;
	Buildings mBuildings;
};
