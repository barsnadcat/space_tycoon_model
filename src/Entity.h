#pragma once

#include "Space.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

class Entity: public Space
{
public:
	using Shared = std::shared_ptr<Entity>;

	Entity(uint32_t health): mHealth(health), mMaxHealth(health) {}
	virtual ~Entity() = default;
	uint32_t GetHealth() const { return mHealth; }
	uint32_t GetMaxHealth() const { return mMaxHealth; }
	void SetHealth(uint32_t health) { mHealth = std::min(health, mMaxHealth); }
	void SetMaxHealth(uint32_t health)
	{
		mMaxHealth = health;
		SetHealth(mHealth);
	}
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

private:
	virtual void OnSpaceUpdated() override
	{
		DamageHealth(1);
		DamageMaxHealth(1);
		OnEntityUpdated();
	}
	virtual void OnEntityUpdated() {}

private:
	uint32_t mHealth { 0 };
	uint32_t mMaxHealth { 0 };
};
