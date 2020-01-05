#pragma once

#include <vector>
#include <cstdint>


template<typename TEntity>
class EntityArray
{
private:
	struct Element
	{
		bool isDeleted { true };
		uint8_t generation { 0 };
		uint32_t previousFree { 0 };
		TEntity entity;
	};

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
			return !(*this == b);
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

	class Iterator
	{
	public:
		Iterator(typename std::vector<Element>::iterator i, 
			typename std::vector<Element>::iterator end): mI(i), mEnd(end)
		{
		}

		bool operator!=(const Iterator& other)
		{
			return other.mI != mI || other.mEnd != mEnd;
		}

		void operator++()
		{
			mI++;
			if (mI != mEnd && mI->isDeleted)
			{
				++(*this);
			}
		}

		TEntity* operator*()
		{
			return &(mI->entity);
		}
	private:
		typename std::vector<Element>::iterator mI;
		typename std::vector<Element>::iterator mEnd;
	};

	Iterator begin()
	{
		return Iterator(mElements.begin(), mElements.end());
	}

	Iterator end()
	{
		return Iterator(mElements.end(), mElements.end());
	}

	EntityArray()
	{
		mElements.resize(1);
	}

	Id Insert(const TEntity& entity)
	{
		uint32_t index = 0;
		if (mFree)
		{
			index = mFree;
			assert(mElements[mFree].isDeleted);
			assert(mElements[mFree].previousFree != mFree);
			mFree = mElements[mFree].previousFree;
		}
		else
		{
			index = mElements.size();
			mElements.push_back({});
		}
		Element& e = mElements[index];
		e.isDeleted = false;
		e.generation++;
		e.entity = entity;
		return {index, e.generation};
	}

	TEntity* Get(const Id id)
	{
		if (id.index < mElements.size())
		{
			Element& e = mElements[id.index];
			if (!e.isDeleted && e.generation == id.generation)
			{
				return &(e.entity);
			}
		}
		return nullptr;
	}

	void Delete(const Id id)
	{
		if (id.index < mElements.size())
		{
			Element& e = mElements[id.index];
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
	uint32_t mFree { 0 };
	std::vector<Element> mElements;
};