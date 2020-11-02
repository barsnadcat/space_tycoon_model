#pragma once

#include <Entity.h>

class Farm: public Entity
{
public:
    Farm(uint32_t health): Entity(health) {}
private:
    virtual void OnEntityUpdated(UpdateContext &uc) override
    {
        OnBuildingUpdated(uc);
    }
    virtual void OnBuildingUpdated(UpdateContext &uc) {}
};