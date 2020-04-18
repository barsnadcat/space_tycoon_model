#pragma once

#include <memory>
#include <cassert>

class IEntity;
class IEntityIterator
{
public:
	using Shared = std::shared_ptr<IEntityIterator>;
	virtual bool HasNext() = 0;
	virtual std::shared_ptr<IEntity> Next() = 0;
	virtual void Remove() = 0;
};

class NullEntityIterator: public IEntityIterator
{
public:
	virtual bool HasNext() { return false; }
	virtual std::shared_ptr<IEntity> Next() { assert(!"You should check HasNext first!"); return nullptr; }
	virtual void Remove() { assert(!"It's a null iterator, there is nothing to remove"); }
};

class IEntityContainer
{
public:
	virtual IEntityIterator::Shared GetEntityIterator() { return std::make_shared<NullEntityIterator>(); }
};