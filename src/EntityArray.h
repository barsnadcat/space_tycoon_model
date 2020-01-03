#pragma once

#include <vector>
#include <cstdint>


template<typename T>
class EntityArray
{
public:
	struct Id
	{
		uint32_t index { 0 };
		uint8_t generation { 0 };

		bool operator==(const Id &b) const
		{
			return b.index == index && b.generation == generation;
		}

		bool operator!=(const Id &b) const
		{
			return b.index != index || b.generation != generation;
		}

		operator bool()
		{
			return index != 0 && generation != 0;
		}
		
		operator size_t() = delete;
		operator uint32_t() = delete;
		operator uint8_t() = delete;
		operator int() = delete;
	};

	EntityArray()
	{
		mEntities.resize(1);
	}

	Id Allocate()
	{
		uint32_t index = 0;
		if (mFree)
		{
			index = mFree;
			mFree = mEntities[mFree].previousFree;
		}
		else
		{
			index = mEntities.size();
			mEntities.push_back(Element());
		}

		mEntities[index].isDeleted = false;
		uint8_t generation = ++(mEntities[index].generation);
		return {index, generation};
	}

	T* Get(Id id)
	{
		if (id.index < mEntities.size() &&
		 !mEntities[id.index].isDeleted &&
		 mEntities[id.index].generation == id.generation)
		{
			return &(mEntities[id.index].entity);
		}
		return nullptr;
	}

	void Delete(Id id)
	{
		if (id.index < mEntities.size())
		{
			mEntities[id.index].isDeleted = true;
			if (mFree)
			{
				mEntities[id.index].previousFree = mFree;
			}
			mFree = id.index;
		}
	}

private:
	struct Element
	{
		bool isDeleted { true };
		uint8_t generation { 0 };
		uint32_t previousFree { 0 };
		T entity;
	};

private:
	uint32_t mFree { 0 };
	std::vector<Element> mEntities;
};