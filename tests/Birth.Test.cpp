#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>

TEST(Person, Birth)
{
	UpdateContext uc;
	Settlement settlement;
	EXPECT_TRUE(settlement.GetPeople().empty());
	auto person = std::make_shared<Person>(30000, 200);
	person->Produce(uc, &settlement, kReproductionId);
	EXPECT_FALSE(settlement.GetPeople().empty());
}
