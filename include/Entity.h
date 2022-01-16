#pragma once

#include <algorithm>
#include <cstdint>
#include <cassert>

#include <UpdateContext.h>

class Entity
{
public:
	Entity() = default;
	Entity(Entity* prv, uint32_t health, uint32_t decayRate): mHealth(health), mMaxHealth(health), mDecayRate(decayRate)
	{
		if (prv)
		{
			Entity* nxt = prv->mNext;
			if (nxt)
			{
				assert(prv == nxt->mPrevious);
				nxt->mPrevious = this;
			}
			prv->mNext = this;

			mPrevious = prv;
			mNext = nxt;
		}
	}

	virtual ~Entity()
	{
		Entity* prv = nullptr;
		if (mPrevious)
		{
			prv = mPrevious;
			assert(mPrevious->mNext == this);
			mPrevious = nullptr;
		}

		Entity* nxt = nullptr;
		if (mNext)
		{
			nxt = mNext;
			assert(mNext->mPrevious = this);
			mNext = nullptr;
		}

		if (prv)
		{
			prv->mNext = nxt;
		}
		if (nxt)
		{
			nxt->mPrevious = prv;
		}
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
		assert(this);
		if (mDecayRate > 0)
		{
			DamageHealth(mDecayRate);
			DamageMaxHealth(mDecayRate);
		}

		OnEntityUpdated(uc);

		if (mPrevious)
		{
			assert(mPrevious->mNext == this);
		}

		if (mNext)
		{
			assert(mNext->mPrevious == this);
			mNext->Update(uc);
		}

		assert(this);
		if (mPrevious != nullptr)
		{
            // Root does not suicide?
			if (mHealth == 0)
			{
				delete this;
			}
		}
	}

private:
	virtual void OnEntityUpdated(UpdateContext& uc) {}
	uint32_t mHealth = 0;
	uint32_t mMaxHealth = 0;
	uint32_t mDecayRate = 1;
	Entity* mNext = nullptr;
	Entity* mPrevious = nullptr;
};
