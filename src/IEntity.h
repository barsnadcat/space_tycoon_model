#pragma once

class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() = default;
	virtual uint32_t GetHealth() const { return 0; }
	virtual void SetHealth(uint32_t health) {}
	virtual void SetMaxHealth(uint32_t health) {}
	virtual void Update(uint32_t days) {}
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

template<typename T>
void Update(std::vector<std::shared_ptr<T>>& inventory, uint32_t days)
{
	for(auto& ptr: inventory)
	{
		ptr->Update(days);
	}
	RemoveDead<T>(inventory);
}
