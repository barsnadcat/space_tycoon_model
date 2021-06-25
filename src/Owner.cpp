#include <Owner.h>
#include <Food.h>
#include <Farm.h>

int32_t Owner::GetOwned(ProductId productId) const
{
	if (productId == kRandomProductId)
	{
		int32_t total = 0;
		for (const auto& p : mInventory)
		{
			total += p.second.size();
		}
		return total;
	}
	else
	{
		const auto& it = mInventory.find(productId);
		if (it == mInventory.end())
		{
			return 0;
		}
		else
		{
			return it->second.size();
		}
	}
}
