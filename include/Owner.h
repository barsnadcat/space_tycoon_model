#pragma once

#include <Entity.h>
#include <vector>

class Food;
class Building;
using Foods = std::vector<Food*>;

class Owner: public Entity
{
public:
	Owner(Entity* prev, uint32_t health, uint32_t decayRate);
	virtual ~Owner();

	void SetBuilding(Building* building) { mBuilding = building; }
	Building* GetBuilding() { return mBuilding; }

	const Foods& GetFoods() const { return mFoods; }
	void AddFood(Food* food);
	void RemoveFood(Food* food);
	void MoveTo(Owner& target);

private:
	virtual void OnEntityUpdated(UpdateContext& uc) override
	{
		OnOwnerUpdated(uc);
	}
	virtual void OnOwnerUpdated(UpdateContext& uc) {}

	virtual void OnEntityDeath(UpdateContext& uc) override;
	Building* mBuilding = nullptr;
	std::vector<Food*> mFoods;
};
