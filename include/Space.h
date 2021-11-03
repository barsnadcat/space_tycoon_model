#pragma once

#include <Entity.h>
#include <Land.h>

#include <cassert>
#include <memory>
#include <vector>

using Lands = std::vector<Land*>;

class Space: public Entity
{
public:
	Space(size_t landSize): Entity(nullptr, 1, 0) 
	{
		mLands.resize(landSize);
		for (size_t i = 0; i < landSize; i++)
		{
			mLands[i] = new Land(this, i);
		}
	}
	virtual ~Space() = default;
	Lands& GetLands() { return mLands; }
	Land* GetLand(size_t index) { return mLands[index]; }
	size_t GetNeighbour(size_t index) { return std::max(mLands.size(), index + 1); }
	void RemoveLand(Land* land)
private:
	virtual void OnEntityUpdated(UpdateContext& uc) override 
	{
		OnSpaceUpdated(uc);
	}
	virtual void OnSpaceUpdated(UpdateContext& uc) {}
	Lands mLands;
};
