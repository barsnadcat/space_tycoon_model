#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Farm.h>

TEST(Person, ScavengeFood)
{
	UpdateContext uc;
	Settlement settlement;
	auto person1 = std::make_shared<Person>(3000, 0);
	auto person2 = std::make_shared<Person>(3000, 0);
	auto food1 = std::make_shared<Food>(100);
	auto food2 = std::make_shared<Food>(100);
	person1->ClaimFood(food1);
	EXPECT_EQ(food1->GetOwner(), person1.get());

	settlement.AddFood(food1);
	settlement.AddFood(food2);
	person2->Produce(uc, &settlement, kScavengeId);
	EXPECT_EQ(food1->GetOwner(), person1.get());
	EXPECT_EQ(food2->GetOwner(), person2.get());
}