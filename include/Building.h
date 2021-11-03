#pragma once

#include <Entity.h>
#include <Owner.h>
#include <vector>

using OwnerPtr = std::unique_ptr<Owner>;
using Owners = std::vector<OwnerPtr>;

class Land;

class Building: public Entity
{
public:
    Building(Entity* prev, uint32_t health, uint32_t decayRate): Entity(prev, health, decayRate) 
    {
        mNobody.reset(new Owner(this, 1, 0));
    }
    virtual ~Building() = default;
    Owner& GetNobody() { return mNobody*; }
    Owners& GetOwners() { return mOwners; }
    void SetLand(Land* land){ mLand = land; }
    Land* GetLand() { return mLand; }
    
    void AddOwner(OwnerPtr owner) 
    {
        owner->SetBuilding(this);
        mOwners.push_back(std::move(owner)); 
    }

    void DeleteOwner(Owner* owner)
    {
        auto predicate = [owner](const OwnerPtr& x){ return x.get() == owner;};
        mOwners.erase(std::remove_if(mOwners.begin(), mOwners.end(), predicate), mOwners.end());
    }

    void MoveTo(Building& target)
    {
        while(!mOwners.empty())
        {
            target.AddOwner(std::move(mOwners.back()));
            mOwners.pop_back();
        }
        mNobody.MoveTo(target.mNobody);
    }
private:
    virtual void OnEntityDeath() override
    {
        mLand->DeleteBuilding(this);
    }
    Land* mLand = nullptr;
    Owners mOwners;    
    OwnerPtr mNobody;
};
using Nothing = Building;