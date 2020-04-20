#pragma once

#include "ISpace.h"

#include <algorithm>
#include <cstdint>
#include <vector>
#include <memory>

class IEntity: public ISpace
{
public:
	using Shared = std::shared_ptr<IEntity>;

	IEntity(uint32_t health): mHealth(health), mMaxHealth(health) {}
	virtual ~IEntity() = default;

	uint32_t GetHealth() const { return mHealth; }
	uint32_t GetMaxHealth() const { return mMaxHealth; }
	void SetHealth(uint32_t health) { mHealth = std::min(health, mMaxHealth); }
	void SetMaxHealth(uint32_t health) { mMaxHealth = health; SetHealth(mHealth); }
	void DecayMaxHealth(uint32_t days)
	{
		if (mMaxHealth > 0)
		{
			SetMaxHealth(mMaxHealth - days);
		}
	}
private:
	uint32_t mHealth { 0 };
	uint32_t mMaxHealth { 0 };
};

