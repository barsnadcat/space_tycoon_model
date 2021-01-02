#pragma once

#include <Owner.h>
#include <Food.h>

#include <memory>
#include <vector>

std::map<ProductId, float> Mutate(UpdateContext& uc, std::map<ProductId, float>);
std::map<ProductId, float> RandomPreferences(UpdateContext& uc);

class Person: public Owner
{
public:
	using Shared = std::shared_ptr<Person>;
	Person(uint32_t health, int32_t energy, const std::map<ProductId, float>& preferences): Owner(health),
		mEnergy(energy), mPreferences(preferences) {}

	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, Space* space, ProductionId productionId);
private:
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const;
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	bool CanDoProduction(UpdateContext& uc, ProductionId productionId) const;
	int32_t GetPersonOwned(ProductId productId) const;
	void Scavenge(Space* space);
	void Reproduce(UpdateContext& uc, Space* space);
private:
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
	std::map<ProductId, float> mPreferences;
};
