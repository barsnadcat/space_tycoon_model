#pragma once

#include <cassert>
#include <memory>
#include <vector>

class Entity;
class Food;
class Person;
struct UpdateContext;

using FoodPtr = std::unique_ptr<Food>;
using Foods = std::vector<FoodPtr>;
using PersonPtr = std::unique_ptr<Person>;
using People = std::vector<PersonPtr>;

class Space
{
public:
	virtual ~Space() {}
	Space* GetParent() { return mParent; }
	void Update(UpdateContext& uc);
	void AddPerson(PersonPtr p);
	void AddFood(FoodPtr p);
	void MoveTo(Space& space);
	Foods& GetFoods() { return mFoods; }
	People& GetPeople() { return mPeople; }

private:
	void SetParent(Space* space) { mParent = space; }
	template<typename T>
	void DeleteEntities(std::vector<std::unique_ptr<T>>& container);
	virtual void OnSpaceUpdated(UpdateContext& uc){}

private:
	Space* mParent = nullptr;
	Foods mFoods;
	People mPeople;
};
