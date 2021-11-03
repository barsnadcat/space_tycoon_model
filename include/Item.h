#pragma once

#include <Entity.h>
#include <EntitiesDeclarations.h>

class Owner;

class Item: public Entity
{
public:
    Item(Entity* prev, uint32_t health, uint32_t decayRate, ProductId productId): 
        Entity(prev, health, decayRate), mProductId(productId) {}
    void SetOwner(Owner* pOwner) { mOwner = pOwner; }
    Owner* GetOwner() { return mOwner; }
private:
    virtual void OnEntityDeath(UpdateContext& uc)
    {
        mOwner->Remove(mProductId, this);
    }
    Owner* mOwner = nullptr;
    const ProductId mProductId;
};