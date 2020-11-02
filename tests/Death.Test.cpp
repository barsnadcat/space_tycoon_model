#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>

TEST(Person, Death)
{
	UpdateContext uc;
	Settlement settlement;
	settlement.AddPerson(std::make_shared<Person>(0, 0));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
}

