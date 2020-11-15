#pragma once

#include <Entity.h>
#include <EntitiesDeclarations.h>
#include <map>

class Owner: public Entity
{
public:
	Owner(uint32_t health): Entity(health) {}
	void ClaimFood(EntitySP food);
	void ClaimFarm(EntitySP building);
	EntityWPs& GetMyFoods() { return mEntities[kFoodId]; }
	FoodSP GetMyNearFood();
	int GetOwned(ProductId productId) const;

private:
	virtual void OnEntityUpdated(UpdateContext& uc)
	{
		OnOwnerUpdated(uc);
	}
	virtual void OnOwnerUpdated(UpdateContext& uc) {}
	std::map<ProductId, EntityWPs> mEntities;
};
