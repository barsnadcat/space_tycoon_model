#pragma once

#include <Entity.h>
#include <vector>
#include <memory>


class Land;

class Farm: public Entity
{
public:
	Farm(Entity* prev, uint32_t health, uint32_t decayRate);
	virtual ~Farm();
	void SetLand(Land* land){ mLand = land; }
	Land* GetLand() { return mLand; }
	
private:
	Land* mLand = nullptr;
};
