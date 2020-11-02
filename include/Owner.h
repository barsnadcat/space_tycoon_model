#pragma once

#include <Entity.h>
#include <EntitiesDeclarations.h>

class Owner: public Entity
{
public:
	Owner(uint32_t health): Entity(health) {}
    void ClaimFood(FoodSP food);
	void ClaimFarm(FarmSP building);
    std::vector<FoodWP>& GetMyFoods() { return mFoods; }
    FoodSP GetMyNearFood();

private:
	virtual void OnEntityUpdated(UpdateContext& uc)
	{
		OnOwnerUpdated(uc);
	}
	virtual void OnOwnerUpdated(UpdateContext& uc) {}

    std::vector<FoodWP> mFoods;
	std::vector<FarmWP> mFarms;
};
