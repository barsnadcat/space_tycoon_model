#pragma once

#include <Entity.h>
#include <Building.h>
using BuildingPtr = std::unique_ptr<Building>;

class Space;

class Land: public Entity
{
public:
	Land(Space* space, size_t index): Entity(space, 1, 0), mNothing(1, 0), mSpace(space), mIndex(index)
	{
		mNothing.SetLand(this);
	}
	virtual ~Land() = default;
    Space* GetSpace() const { return mSpace; }
	size_t GetIndex() const { return mIndex; }
	void SetBuilding(BuildingPtr building)
	{
		mBuilding = std::move(building);
	}
	void DeleteBuilding(Building* building)
	{
		assert(mBuiling.get() == building);
		mBuilding->MoveTo(mNothing);
		mBuilding.reset();
	}
	Building* GetBuilding() { return mBuilding.get(); }
	Building& GetNothing() { return mNothing; }
private:
    Space* const mSpace = nullptr;
	const size_t mIndex = 0;
	Building mNothing;
	BuildingPtr mBuilding;
};
