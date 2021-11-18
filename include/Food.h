#pragma once

#include <Entity.h>

class Land;

class Food: public Entity
{
public:
	Food(Entity* prev, uint32_t health, uint32_t decayRate):
		Entity(prev, health, decayRate){}
	virtual ~Food();
	int32_t GetEnergy() { return 3; }
	void SetLand(Land* pLand) { mLand = pLand; }
	Land* GetLand() { return mLand; }
private:
	Land* mLand = nullptr;
};
