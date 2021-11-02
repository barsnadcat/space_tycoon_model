#pragma once

#include <algorithm>
#include <cstdint>

#include <UpdateContext.h>

class Entity
{
public:
	Entity() = default;
	Entity(uint32_t health, uint32_t decayRate): mHealth(health), mMaxHealth(health), mDecayRate(decayRate) {}
	virtual ~Entity() = default;
	uint32_t GetDecayRate() const { return mDecayRate; }
	void SetDecayRate(uint32_t decaryRate) { mDecayRate = decaryRate; }
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
		if (mDecayRate > 0)
		{
			DamageHealth(mDecayRate);
			DamageMaxHealth(mDecayRate);
		}
		OnEntityUpdated(uc);
	}

private:
	virtual void OnEntityUpdated(UpdateContext& uc) {}
	uint32_t mHealth = 0;
	uint32_t mMaxHealth = 0;
	uint32_t mDecayRate = 1;
};


template<typename T>
void UpdateEntities(T& container, UpdateContext& uc)
{
	for (auto const& e: container)
	{
		e->Update(uc);
	}
	auto predicate = [](auto const& e)
	{
		return e->GetHealth() == 0;
	};
	container.erase(std::remove_if(std::begin(container), std::end(container), predicate), std::end(container));
}
