#include <gtest/gtest.h>
#include <easylogging++.h>

#include <Food.h>


TEST(EntityVector, RemoveDead) 
{
	// Dead entities have to be removed from vector.
	std::vector<std::shared_ptr<Food>> inventory;
	std::shared_ptr<Food> food = std::make_shared<Food>();
	food->SetHealth(0);
	inventory.push_back(food);
	food.reset();
	RemoveDead<Food>(inventory);
	EXPECT_TRUE(inventory.empty());
}


TEST(EntityVector, Udpate) 
{
	// Update entities, and remove dead ones
	std::vector<std::shared_ptr<Food>> inventory;
	std::shared_ptr<Food> food = std::make_shared<Food>();
	food->SetHealth(3);
	food->SetMaxHealth(3);
	inventory.push_back(food);
	food.reset();
	Update<Food>(inventory, 2);
	EXPECT_EQ(inventory.begin()->get()->GetHealth(), 1);
	Update<Food>(inventory, 1);
	EXPECT_TRUE(inventory.empty());
}
