#include <Owner.h>
#include <Food.h>

void Owner::ClaimFood(std::shared_ptr<Food> food)
{
	food->SetOwner(std::static_pointer_cast<Owner>(shared_from_this()));
	mFoods.push_back(food);
}

std::shared_ptr<Food> Owner::GetMyNearFood()
{
	for (auto it = mFoods.begin(); it != mFoods.end();)
	{
        std::shared_ptr<Food> food = (*it).lock();
		if (food)
		{
            if (food->GetParent() == GetParent())
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
}
