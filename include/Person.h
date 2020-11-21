#pragma once

#include <Owner.h>
#include <Food.h>

#include <memory>
#include <vector>

class Person: public Owner
{
public:
	using Shared = std::shared_ptr<Person>;
	Person(uint32_t health, int32_t energy, bool likeToBuild, bool likeToFarm): Owner(health),
		mEnergy(energy), mLikeToFarm(likeToFarm), mLikeToBuild(likeToBuild) {}

	float GetMarginalUtility(UpdateContext& uc, ProductId productId, int32_t number) const;
	float GetPersonalPreference(ProductId) const { return 1.0f; }
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
private:
	
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	void Scavenge();
	void Reproduce(UpdateContext& uc);
	void Produce(UpdateContext& uc, ProductionId productionId);
private:
	bool mLikeToBuild = false;
	bool mLikeToFarm = false;
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
};
