#pragma once

#include <Entity.h>

class Food;

using FoodWeakPtr = std::weak_ptr<Food>;
using FoodWeakPtrs = std::vector<FoodWeakPtr>;

class Owner: public Entity
{
public:
	Owner(uint32_t health): Entity(health) {}
    void ClaimFood(std::shared_ptr<Food> food);
    FoodWeakPtrs& GetMyFoods() { return mFoods; }
    std::shared_ptr<Food> GetMyNearFood();

private:
	virtual void OnEntityUpdated(UpdateContext& uc)
	{
		OnOwnerUpdated(uc);
	}
	virtual void OnOwnerUpdated(UpdateContext& uc) {}
    FoodWeakPtrs mFoods;
};
