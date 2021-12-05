#pragma once

#include <Entity.h>

#include <memory>
#include <vector>

class Land;
using LandPtr = std::unique_ptr<Land>;
using Lands = std::vector<LandPtr>;

class Settlement: public Entity
{
public:
	Settlement(size_t landSize);
	virtual ~Settlement();

	Lands& GetLands() { return mLands; }
	Land& GetLand(size_t index) { return *(mLands[index]); }
	Land* GetNeighbour(Land* land) const;
private:
	Lands mLands;
};
