#include <gtest/gtest.h>
#include <easylogging++.h>

#include <Food.h>


TEST(EntityVector, RemoveDead) 
{
	// Dead entities have to be removed from vector.
	std::vector<std::shared_ptr<Food>> inventory;
	std::shared_ptr<Food> food = std::make_shared<Food>(100);
	food->SetHealth(0);
	inventory.push_back(food);
	food.reset();
	RemoveDead<Food>(inventory);
	EXPECT_TRUE(inventory.empty());
}

