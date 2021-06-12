#pragma once

#include <Entity.h>
class Owner;

class Item: public Entity
{
public:
    Item(uint32_t health, uint32_t decayRate): Entity(health, decayRate) {}
    void SetOwner(Owner* pOwner) { mOwner = pOwner; }
    Owner* GetOwner() { return mOwner; }
private:
    Owner* mOwner = nullptr;
};