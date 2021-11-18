#pragma once

#include <Entity.h>

class Land;
class Food;
using Foods = std::vector<Food*>;

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float> );
std::map<ProductId, float> RandomPreferences(UpdateContext& uc);

class Person: public Entity
{
public:
	Person(Entity* prev, uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences): Owner(prev, health, 1),
		mEnergy(energy), mPreferences(preferences) {}
	~Person();

	void SetLand(Land* pLand) { mLand = pLand; }
	Land* GetLand() { return mLand; }

	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, ProductionId productionId);
private:
	virtual void OnEntityUpdated(UpdateContext& uc) override;
	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const;
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	bool CanDoProduction(UpdateContext& uc, ProductionId productionId) const;
	int32_t GetPersonOwned(ProductId productId) const;
	void Scavenge();
	void Reproduce(UpdateContext& uc);
private:
	Land* mLand = nullptr;
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
	std::map<ProductId, float> mPreferences;
};
