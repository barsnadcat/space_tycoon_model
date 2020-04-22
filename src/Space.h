#pragma once

#include <vector>
#include <memory>
#include <cassert>

class Entity;
class IEntityIterator
{
public:
	using Shared = std::shared_ptr<IEntityIterator>;
	virtual bool HasNext() = 0;
	virtual void Next() = 0;
	virtual std::shared_ptr<Entity> Get() = 0;
	virtual void Remove() = 0;
};

class NullEntityIterator: public IEntityIterator
{
public:
	virtual bool HasNext() { return false; }
	virtual void Next() { assert(!"You should check HasNext first!"); }
	virtual std::shared_ptr<Entity> Get() { assert(!"It's a null iterator, there is nothing to get!"); return nullptr; }
	virtual void Remove() { assert(!"It's a null iterator, there is nothing to remove"); }
};

template<typename T>
class VectorEntityIterator: public IEntityIterator
{
public:
	VectorEntityIterator(std::vector<T>& vector): mVector(vector) {	mIt = mVector.begin(); }
	virtual bool HasNext() override	{ return mIt != mVector.end(); }
	virtual std::shared_ptr<Entity> Get() override { return *mIt; }
	virtual void Next() override { assert(HasNext()); mIt++; }
	virtual void Remove() override { mIt = mVector.erase(mIt); }
private:
	std::vector<T>& mVector;
	typename std::vector<T>::iterator mIt;
};

class Space
{
public:
	virtual IEntityIterator::Shared GetEntityIterator() { return std::make_shared<NullEntityIterator>(); }
};