#pragma once

#include <Owner.h>
#include <Food.h>

#include <memory>
#include <vector>

class Person: public Owner
{
public:
	using Shared = std::shared_ptr<Person>;
	Person(uint32_t health, int32_t energy): Owner(health), mEnergy(energy) {}

private:
	virtual void OnOwnerUpdated(UpdateContext& uc) override;
	void Scavenge();
private:
	int32_t mEnergy { 0 };
};
