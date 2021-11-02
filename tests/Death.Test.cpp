#include <src/easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Building.h>
#include <Person.h>

TEST_F(UpdateContextTestFixture, Death)
{
	Building building(1, 0);
	building.AddOwner(std::unique_ptr<Person>(new Person(0, 0, {})));
	EXPECT_FALSE(building.GetOwners().size() == 1);
	building.Update(uc);
	EXPECT_TRUE(building.GetOwners().size() == 0);
}

