#include <Owner.h>
#include <Food.h>

void Owner::ClaimFood(FoodSP food)
{
	food->SetOwner(std::static_pointer_cast<Owner>(shared_from_this()));
	mFoods.push_back(food);
}

FoodSP Owner::GetMyNearFood()
{
	for (auto it = mFoods.begin(); it != mFoods.end();)
	{
        FoodSP food = (*it).lock();
		if (food)
		{
            if (food->GetParent() == GetParent() && food->GetHealth() > 0)
            {
                return food;
            }
            else
            {
                it++;
            }            
		}
		else
		{
            it = mFoods.erase(it);
		}
	}
	return nullptr;
}
