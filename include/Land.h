#pragma once

#include <Entity.h>
#include <memory>

class Space;
class Building;

class Land: public Entity
{
public:
	Land(Space* space, size_t index);
	virtual ~Land();

	Space* GetSpace() const { return mSpace; }
	size_t GetIndex() const { return mIndex; }
	void AddBuilding(Building* building);
	void RemoveBuilding(Building* building);
	Building& GetBuilding() { return *mNullBuilding; }
private:
	Space* const mSpace = nullptr;
	const size_t mIndex = 0;
	std::unique_ptr<Building> mBuilding;
};
