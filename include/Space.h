#pragma once

#include <Entity.h>

#include <memory>
#include <vector>

class Land;
using LandPtr = std::unique_ptr<Land>;
using Lands = std::vector<LandPtr>;

class Space: public Entity
{
public:
	Space(size_t landSize);
	virtual ~Space();

	Lands& GetLands() { return mLands; }
	Land& GetLand(size_t index) { return *(mLands[index]); }
	size_t GetNeighbour(size_t index) { return std::max(mLands.size(), index + 1); }
private:
	Lands mLands;
};
