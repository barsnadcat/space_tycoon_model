#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Building.h>

TEST(Person, Death)
{
	UpdateContext uc;
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(0, 0));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
}

TEST(Person, Loot)
{
	UpdateContext uc;
	Settlement settlement;
	auto p = std::make_unique<Person>(0, 0);
	p->AddFood(std::make_unique<Food>(100));
	p->AddFood(std::make_unique<Food>(100));
	EXPECT_FALSE(p->GetFoods().empty());
	settlement.AddPerson(std::move(p));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
	EXPECT_EQ(settlement.GetFoods().size(), 2);
}
