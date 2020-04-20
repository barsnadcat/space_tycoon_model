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
	void DamageHealth(uint32_t health)
	{
		if (health > mHealth)
		{
			mHealth = 0;
		}
		else
		{
			mHealth -= health;
		}
	}
	void DamageMaxHealth(uint32_t health)
	{
		if (health > mMaxHealth)
		{
			mMaxHealth = 0;
		}
		else
		{
			mMaxHealth -= health;
		}

	}
	void Update()
	{
		DamageHealth(1);
		DamageMaxHealth(1);
		EntityChildUpdate();
	}
private:
	virtual void EntityChildUpdate() {}
private:
	uint32_t mHealth { 0 };
	uint32_t mMaxHealth { 0 };
};

