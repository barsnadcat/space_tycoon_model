#include <Owner.h>
#include <Food.h>

void Owner::ClaimFood(std::shared_ptr<Food> food)
{
    food->SetOwner(std::static_pointer_cast<Owner>(shared_from_this()));
    mFoods.push_back(food);
}