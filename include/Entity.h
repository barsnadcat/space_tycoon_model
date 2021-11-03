#pragma once

#include <algorithm>
#include <cstdint>
#include <cassert>

#include <UpdateContext.h>

class Entity
{
public:
	Entity() = default;
	Entity(Entity* prev, uint32_t health, uint32_t decayRate): mHealth(health), mMaxHealth(health), mDecayRate(decayRate) 
	{
		if (prev)
		{
			mPrevious = prev;
			mPrevious->mNext = this;
			if (prev->mNext)
			{
				mNext = prev->mNext;
				mNext->mPrevious = this;
			}
		}
	}

	virtual ~Entity()
	{
		if (mPrevious)
		{
			mPrevious->mNext = mNext;
			mPrevious = nullptr;
			if (mNext)
			{
				mNext->mPrevious = mPrevious;
				mNext = nullptr;
			}
		}
		assert(mNext == nullptr);
	}
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

		if (mNext)
		{
			mNext->Update(uc);
		}

		if (mHealth == 0)
		{
			OnEntityDeath();
		}
	}

private:
	virtual void OnEntityUpdated(UpdateContext& uc) {}
	virtual void OnEntityDeath(UpdateContext& uc) {}
	uint32_t mHealth = 0;
	uint32_t mMaxHealth = 0;
	uint32_t mDecayRate = 1;
	Entity* mNext = nullptr;
	Entity* mPrevious = nullptr;
};
