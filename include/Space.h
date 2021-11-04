#pragma once

#include <Entity.h>
#include <Land.h>

#include <cassert>
#include <memory>
#include <vector>

using LandPtr = std::unique_ptr<Land>;
using Lands = std::vector<LandPtr>;

class Space: public Entity
{
public:
	Space(size_t landSize): Entity(nullptr, 1, 0) 
	{
		mLands.resize(landSize);
		for (size_t i = 0; i < landSize; i++)
		{
			mLands[i].reset(new Land(this, i));
		}
	}
	virtual ~Space() = default;
	Lands& GetLands() { return mLands; }
	Land* GetLand(size_t index) { return mLands[index].get(); }
	size_t GetNeighbour(size_t index) { return std::max(mLands.size(), index + 1); }
private:
	Lands mLands;
};
