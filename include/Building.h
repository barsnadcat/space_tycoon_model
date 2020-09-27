#pragma once

#include <Entity.h>

class Building: public Entity
{
public:
    Building(uint32_t health): Entity(health) {}
private:
    virtual void OnEntityUpdated(UpdateContext &uc) override
    {
        OnBuildingUpdated(uc);
    }
    virtual void OnBuildingUpdated(UpdateContext &uc) {}
};