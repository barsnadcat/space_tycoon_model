#pragma once

class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() = default;
	virtual uint8_t GetHealth() const { return 0; }
	virtual void SetHealth(uint8_t health) {}

	virtual void Update() {}
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
