#pragma once

#include <Entity.h>

class Land;
class Food;
using Foods = std::vector<Food*>;
class Farm;
using Farms = std::vector<Farm*>;

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float> );
std::map<ProductId, float> RandomPreferences(UpdateContext& uc);

class Person: public Entity
{
public:
	Person(Land* land, uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences);
	~Person();

	void SetLand(Land* pLand) { mLand = pLand; }
	Land* GetLand() { return mLand; }

	void AddFood(Food* p);
	void RemoveFood(Food* p);
	Foods& GetFoods() { return mFoods; }
	void AddFarm(Farm* p);
	void RemoveFarm(Farm* p);
	Farms& GetFarms() { return mFarms; }

	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, ProductionId productionId);
	int32_t GetPersonOwned(ProductId productId) const;
private:
	virtual void OnEntityUpdated(UpdateContext& uc) override;
	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const;
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	bool CanDoProduction(UpdateContext& uc, ProductionId productionId) const;
	void Scavenge();
	void Reproduce(UpdateContext& uc);
private:
	Land* mLand = nullptr;
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
	std::map<ProductId, float> mPreferences;
	Foods mFoods;
	Farms mFarms;
};
