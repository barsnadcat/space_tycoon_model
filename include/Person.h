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

private:
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	void Scavenge();
private:
	bool mLikeToBuild = false;
	bool mLikeToFarm = false;
	int32_t mEnergy { 0 };
};
