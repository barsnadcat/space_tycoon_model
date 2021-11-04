#pragma once

#include <Owner.h>
#include <Food.h>

#include <memory>
#include <vector>
#include <cassert>

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float>);
std::map<ProductId, float> RandomPreferences(UpdateContext& uc);

class Person: public Owner
{
public:
	Person(Entity* prev, uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences): Owner(prev, health, 1),
		mEnergy(energy), mPreferences(preferences) {}
	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, ProductionId productionId);
private:
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const;
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	bool CanDoProduction(UpdateContext& uc, ProductionId productionId) const;
	int32_t GetPersonOwned(ProductId productId) const;
	void Scavenge();
	void Reproduce(UpdateContext& uc);
private:
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
	std::map<ProductId, float> mPreferences;
};
