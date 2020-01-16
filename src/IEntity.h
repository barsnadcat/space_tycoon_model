#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <memory>

class IEntity
{
public:
	IEntity(int32_t health): mHealth(health), mMaxHealth(health) {}
	virtual ~IEntity() = default;
	int32_t GetHealth() const { return mHealth; }
	int32_t GetMaxHealth() const { return mMaxHealth; }
	void SetHealth(int32_t health) { mHealth = std::max(0, std::min(health, mMaxHealth)); }
	void IncreaseHealth(int32_t change) { SetHealth(mHealth + change); }
	void DecayMaxHealth(int32_t days) { mMaxHealth = std::max(0, mMaxHealth - days); IncreaseHealth(-days); }
private:
	int32_t mHealth { 0 };
	int32_t mMaxHealth { 0 };
};

template<typename T>
void RemoveDead(std::vector<std::shared_ptr<T>>& inventory)
{
	inventory.erase(
		std::remove_if(inventory.begin(), inventory.end(),
			[](std::shared_ptr<T> ptr)
			{
				return !ptr->GetHealth();
			}),
		inventory.end());
}


