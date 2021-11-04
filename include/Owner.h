#pragma once

#include <Entity.h>
#include <Item.h>
#include <Food.h>

#include <cassert>

using ItemPtr = std::unique_ptr<Item>;
using Items = std::vector<ItemPtr>;

class Building;

class Owner: public Entity
{
public:
	Owner(Entity* prev, uint32_t health, uint32_t decayRate): Entity(prev, health, decayRate) {}
	virtual ~Owner()
	{
		mBuilding->RemoveOwner(this);
	}
	void SetBuilding(Building* building) { mBuilding = building; }
	Building* GetBuilding() { return mBuilding; }
	Items& Get(ProductId productId) { return mInventory[productId]; }
	
	template<typename TItem>
	std::unique_ptr<TItem> Take(ProductId productId)
	{
		std::unique_ptr<TItem> res;
		auto it = mInventory.find(productId);
		if (it != mInventory.end() && !it->second.empty())
		{
			res = std::move(it.second.back());
			it->second.pop_back();
		}
		return res;
	}
	void AddItem(ProductId productId, ItemPtr item)
	{
		assert(item);
		item->SetOwner(this);
		mInventory[productId].push_back(std::move(item));
	}

	void RemoveItem(ProductId productId, Item* item)
	{
		auto predicate = [item](const ItemPtr& x){ return x.get() == item; };
		auto& inventory = mInventory[productId];
		auto it = std::find_if(inventory.begin(), inventory.end(), predicate);
		if (it != inventory.end())
		{
			it->release();
			inventory.erase(it);
		}
	}

	void MoveTo(Owner& target)
	{
		for (auto it = mInventory.begin(); it != mInventory.end(); it++)
		{
			ProductId productId = it->first;
			Items& items = it->second;
			while (!items.empty())
			{
				target.AddItem(productId, std::move(items.back()));
				items.pop_back();
			}
		}
	}
	int32_t GetOwned(ProductId productId) const;

private:
	virtual void OnEntityUpdated(UpdateContext& uc) override
	{
		OnOwnerUpdated(uc);
	}
	virtual void OnEntityDeath(UpdateContext& uc) override
	{
		MoveTo(mBuilding->GetNobody());
	}
	virtual void OnOwnerUpdated(UpdateContext& uc) {}
	Building* mBuilding = nullptr;
	std::map<ProductId, Items> mInventory;
};
