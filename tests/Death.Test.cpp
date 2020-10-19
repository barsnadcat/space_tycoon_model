#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Building.h>

TEST(Person, Death)
{
	UpdateContext uc;
	Settlement settlement;
	settlement.AddPerson(std::make_shared<Person>(0, 0));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
}

TEST(Person, Loot)
{
	UpdateContext uc;
	Settlement settlement;
	auto f1 = std::make_shared<Food>(100);
	auto f2 = std::make_shared<Food>(100);
	auto p = std::make_shared<Person>(0, 0);
	p->ClaimFood(f1);
	p->ClaimFood(f2);
	EXPECT_FALSE(p->GetMyFoods().empty());
	settlement.AddFood(f1);
	settlement.AddFood(f2);
	f1 = nullptr;
	f2 = nullptr;
	settlement.AddPerson(p);
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
	EXPECT_EQ(settlement.GetFoods().size(), 2);
}
