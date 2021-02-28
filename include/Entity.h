#pragma once

#include <Object.h>
#include <EntitiesDeclarations.h>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <memory>

struct UpdateContext;

class Entity
{
public:
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

	void Update(UpdateContext& uc)
	{
		DamageHealth(1);
		DamageMaxHealth(1);
	}

	void SetParent(ObjectSP space) { mParent = space; }
	ObjectSP GetParent() { return mParent.lock(); }

private:
	ObjectWP mParent;
	uint32_t mHealth { 0 };
	uint32_t mMaxHealth { 0 };
};
