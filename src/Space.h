#pragma once

#include <cassert>
#include <memory>
#include <vector>

class Entity;
class Food;
class Person;

using Foods = std::vector<std::unique_ptr<Food>>;
using People = std::vector<std::unique_ptr<Person>>;

class Space
{
public:
	virtual ~Space() {}
	void Update();
	void AddPerson(std::unique_ptr<Person> person) { mPeople.push_back(std::move(person)); }
	void AddFood(std::unique_ptr<Food> person) { mFoods.push_back(std::move(person)); }
	void MoveTo(Space& space);
	Foods& GetFoods() { return mFoods; }
	People& GetPeople() { return mPeople; }

private:
	template <typename T>
	void DeleteEntities(std::vector<std::unique_ptr<T>>& container);
	virtual void OnSpaceUpdated(){};

private:
	Foods mFoods;
	People mPeople;
};