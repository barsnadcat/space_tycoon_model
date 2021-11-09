#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Building.h>
#include <Person.h>

TEST_F(UpdateContextTestFixture, Death)
{
	Settlement settlement(1);
	Land& land = Settlement.GetLand(0);
	Building building(1, 0);
	building.AddOwner(std::unique_ptr<Person>(new Person(0, 0, {})));
	EXPECT_FALSE(building.GetOwners().size() == 1);
	building.Update(uc);
	EXPECT_TRUE(building.GetOwners().size() == 0);
}

