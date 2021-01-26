#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>

TEST_F(UpdateContextTestFixture, Death)
{
	Settlement settlement;
	settlement.AddPerson(std::shared_ptr<Person>(new Person(0, 0, {})));
	EXPECT_FALSE(settlement.GetPeople().empty());
	settlement.Update(uc);
	EXPECT_TRUE(settlement.GetPeople().empty());
}

