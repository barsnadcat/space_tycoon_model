#pragma once

#include <Entity.h>
#include <vector>

class Owner;
using Owners = std::vector<Owner*>;

class Land;

class Building: public Entity
{
public:
	Building(Entity* prev, uint32_t health, uint32_t decayRate);
	virtual ~Building();
	Owner& GetNullOwner() { return *mNullOwner; }
	Owners& GetOwners() { return mOwners; }
	void SetLand(Land* land){ mLand = land; }
	Land* GetLand() { return mLand; }

	void AddOwner(Owner* owner);
	void RemoveOwner(Owner* owner);

	void MoveTo(Building& target);
private:
	virtual void OnEntityDeath(UpdateContext& uc) override;

	Land* mLand = nullptr;
	Owners mOwners;
	std::unique_ptr<Owner> mNullOwner;
};
