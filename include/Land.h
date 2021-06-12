#pragma once

#include <Entity.h>
#include <Building.h>
using BuildingPtr = std::unique_ptr<Building>;

class Space;

class Land: public Entity
{
public:
	Land(Space* space, size_t index): Entity(1, 0), mNothing(1, 0), mSpace(space), mIndex(index)
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
	Building* GetBuilding() { return mBuilding.get(); }
	Building& GetNothing() { return mNothing; }
	virtual void OnEntityUpdated(UpdateContext& uc) override
	{
		mNothing.Update(uc);
		mBuilding->Update(uc);
		if (mBuilding->GetHealth() == 0)
		{
			mBuilding->MoveTo(mNothing);
			mBuilding.reset();
		}
		OnLandUpdated(uc);
	}
	virtual void OnLandUpdated(UpdateContext& uc) {}
private:
    Space* const mSpace = nullptr;
	const size_t mIndex = 0;
	Building mNothing;
	BuildingPtr mBuilding;
};
