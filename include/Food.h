#pragma once

#include <Entity.h>

class Owner;

class Food: public Entity
{
public:
	Food(Entity* prev, uint32_t health, uint32_t decayRate):
		Entity(prev, health, decayRate){}
	virtual ~Food();
	int32_t GetEnergy() { return 3; }
	void SetOwner(Owner* pOwner) { mOwner = pOwner; }
	Owner* GetOwner() { return mOwner; }
private:
	Owner* mOwner = nullptr;
};
