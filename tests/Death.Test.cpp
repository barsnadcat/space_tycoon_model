#include <gtest/gtest.h>
#include <easylogging++.h>

#include "Settlement.h"


TEST(Container, PersonDeath) 
{
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(0, 0));
	EXPECT_TRUE(settlement.GetPersonIterator().HasNext());
    settlement.Update();
	EXPECT_FALSE(settlement.GetPersonIterator().HasNext());
}

TEST(Container, Loot)
{
	Settlement settlement;
	auto p = std::make_unique<Person>(0, 0);
	p->AddFood(std::make_unique<Food>(100));
	p->AddFood(std::make_unique<Food>(100));
	EXPECT_TRUE(p->GetFoodIterator().HasNext());
	settlement.AddPerson(std::move(p));
	EXPECT_TRUE(settlement.GetPersonIterator().HasNext());
    settlement.Update();
	EXPECT_FALSE(settlement.GetPersonIterator().HasNext());
	EXPECT_TRUE(settlement.GetFoodIterator().HasNext());
}


