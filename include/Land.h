#pragma once

#include <Entity.h>
#include <Building.h>
#include <cassert>

using BuildingPtr = std::unique_ptr<Building>;

class Space;

class Land: public Entity
{
public:
	Land(Space* space, size_t index): Entity(space, 1, 0), mSpace(space), mIndex(index)
	{
		mNothing.reset(new Building(this, 1, 0));
	}
	virtual ~Land() = default;
    Space* GetSpace() const { return mSpace; }
	size_t GetIndex() const { return mIndex; }
	void SetBuilding(BuildingPtr building)
	{
		assert(mBuilding == nullptr);
		mBuilding = std::move(building);
		mBuilding->SetLand(this);
	}
	Building* GetBuilding() { return mBuilding.get(); }
	Building& GetNothing() { return *mNothing; }
private:
    Space* const mSpace = nullptr;
	const size_t mIndex = 0;
	BuildingPtr mNothing;
	BuildingPtr mBuilding;
};
