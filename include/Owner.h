#pragma once

#include <Entity.h>

class Owner: public Entity
{
public:
    Owner(uint32_t health): Entity(health) {}
    
private:    
	virtual void OnEntityUpdated(UpdateContext& uc) 
    {
        OnOwnerUpdated(uc);        
    }
    virtual void OnOwnerUpdated(UpdateContext& uc) {}
};