#pragma once

#include <vector>
#include <memory>
#include <cassert>

class Entity;
class Food;
class Person;

class SpaceIterator
{
public:
	SpaceIterator(std::vector<std::unique_ptr<Food>>& foods, std::vector<std::unique_ptr<Person>>& people) : mFoods(foods), mPeople(people), mFoodIt(foods.begin()), mPersonIt(people.begin()) {}
	bool HasNext();
	Entity& Get();
	void Next();
	void Remove();
private:
	std::vector<std::unique_ptr<Food>>& mFoods;
	std::vector<std::unique_ptr<Person>>& mPeople;
	typename std::vector<std::unique_ptr<Food>>::iterator mFoodIt;
	typename std::vector<std::unique_ptr<Person>>::iterator mPersonIt;
};

template<typename T>
class VectorSpaceIterator
{
public:
	VectorSpaceIterator(std::vector<std::unique_ptr<T>>& vector): mVector(vector), mIt(vector.begin()) { }
	bool HasNext() { return mIt != mVector.end(); }
	T& Get() { return **mIt; }
	void Next() { assert(HasNext()); mIt++; }
	void Remove() { mIt = mVector.erase(mIt); }
private:
	std::vector<std::unique_ptr<T>>& mVector;
	typename std::vector<std::unique_ptr<T>>::iterator mIt;
};

class Space
{
public:
	VectorSpaceIterator<Food> GetFoodIterator() { return VectorSpaceIterator<Food>(mFoods); }
	VectorSpaceIterator<Person> GetPersonIterator() { return VectorSpaceIterator<Person>(mPeople); }
	void AddPerson(std::unique_ptr<Person> person) { mPeople.push_back(std::move(person)); }
	void AddFood(std::unique_ptr<Food> person) { mFoods.push_back(std::move(person)); }
	SpaceIterator GetSpaceIterator() { return SpaceIterator(mFoods, mPeople); };
private:
	std::vector<std::unique_ptr<Food>> mFoods;
	std::vector<std::unique_ptr<Person>> mPeople;
};