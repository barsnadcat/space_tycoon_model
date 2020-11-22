#pragma once

#include <Owner.h>
#include <Food.h>

#include <memory>
#include <vector>

class Person: public Owner
{
public:
	using Shared = std::shared_ptr<Person>;
	Person(uint32_t health, int32_t energy): Owner(health),
		mEnergy(energy) {}

	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, Space* space, ProductionId productionId);
private:
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const { return 1.0f; }
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	void Scavenge(Space* space);
	void Reproduce(UpdateContext& uc, Space* space);
private:
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
};
