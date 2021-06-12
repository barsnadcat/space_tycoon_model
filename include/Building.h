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
    Building(uint32_t health, uint32_t decayRate): Entity(health, decayRate), mNobody(1, 0) {}
    virtual ~Building() = default;
    Owner& GetNobody() { return mNobody; }
    Owners& GetOwners() { return mOwners; }
    void SetLand(Land* land){ mLand = land; }
    Land* GetLand() { return mLand; }
    void AddOwner(OwnerPtr owner) 
    {
        owner->SetBuilding(this);
        mOwners.push_back(std::move(owner)); 
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
    virtual void OnEntityUpdated(UpdateContext& uc) override { mNobody.Update(uc); UpdateEntities(mOwners, uc); OnBuildingUpdated(uc); }
    virtual void OnBuildingUpdated(UpdateContext& uc) {};
    Land* mLand = nullptr;
    Owners mOwners;    
    Owner mNobody;
};
using Nothing = Building;