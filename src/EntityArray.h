#pragma once

#include <vector>

template<typename T>
class EntityArray
{
public:
	EntityArray()
	{
		mEntities.resize(1);
	}
	
	size_t Allocate()
	{
		size_t result = 0;
		if (mFree)
		{
			result = mFree;
			mFree = mEntities[mFree].previousFree;
		}
		else
		{
			result = mEntities.size();
			mEntities.push_back(Element());
		}

		mEntities[result].isDeleted = false;
		return result;
	}

	T* Get(size_t id)
	{
		if (id < mEntities.size() && !mEntities[id].isDeleted)
		{
			return &(mEntities[id].entity);
		}
		return nullptr;
	}
private:
	struct Element
	{
		bool isDeleted { true };
		size_t previousFree { 0 };
		T entity;
	};

private:
	size_t mFree { 0 };
	std::vector<Element> mEntities;
};