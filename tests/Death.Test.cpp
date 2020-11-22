#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>

TEST(Person, Death)
{
	UpdateContext uc;
	Settlement settlement;
	settlement.AddPerson(std::shared_ptr<Person>(new Person(0, 0, {})));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
}

