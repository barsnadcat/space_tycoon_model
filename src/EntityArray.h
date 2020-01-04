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

		operator bool() const
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

	Id Insert(const T& entity)
	{
		uint32_t index = 0;
		if (mFree)
		{
			index = mFree;
			assert(mEntities[mFree].isDeleted);
			assert(mEntities[mFree].previousFree != mFree);
			mFree = mEntities[mFree].previousFree;
		}
		else
		{
			index = mEntities.size();
			mEntities.push_back({});
		}
		Element& e = mEntities[index];
		e.isDeleted = false;
		e.generation++;
		e.entity = entity;
		return {index, e.generation};
	}

	T* Get(const Id id)
	{
		if (id.index < mEntities.size())
		{
			Element& e = mEntities[id.index];
			if (!e.isDeleted && e.generation == id.generation)
			{
				return &(e.entity);
			}
		}
		return nullptr;
	}

	void Delete(const Id id)
	{
		if (id.index < mEntities.size())
		{
			Element& e = mEntities[id.index];
			if (!e.isDeleted)
			{
				e.isDeleted = true;
				if (mFree)
				{
					e.previousFree = mFree;
				}
				mFree = id.index;
			}
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

	uint32_t mFree { 0 };
	std::vector<Element> mEntities;
};