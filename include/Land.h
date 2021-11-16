#pragma once

#include <Entity.h>
#include <memory>

class Settlement;
class Building;

class Land: public Entity
{
public:
	Land(Settlement* settlement, size_t index);
	virtual ~Land();

	Settlement* GetSpace() const { return mSettlement; }
	size_t GetIndex() const { return mIndex; }
	void AddBuilding(Building* building);
	void RemoveBuilding(Building* building);
	Building* GetBuilding() { return mBuilding; }
	Building& GetNullBuilding() { return *mNullBuilding; }
private:
	Settlement* const mSettlement = nullptr;
	const size_t mIndex = 0;
	std::unique_ptr<Building> mNullBuilding;
	Building* mBuilding;
};
