#include <easylogging++.h>
#include <gtest/gtest.h>

#include "Settlement.h"

TEST(Container, PersonDeath)
{
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(0, 0));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update();
	EXPECT_TRUE(settlement.GetPeople().empty());
}

TEST(Container, Loot)
{
	Settlement settlement;
	auto p = std::make_unique<Person>(0, 0);
	p->AddFood(std::make_unique<Food>(100));
	p->AddFood(std::make_unique<Food>(100));
	EXPECT_FALSE(p->GetFoods().empty());
	settlement.AddPerson(std::move(p));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update();
	EXPECT_TRUE(settlement.GetPeople().empty());
	EXPECT_EQ(settlement.GetFoods().size(), 3);
}
