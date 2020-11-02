#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Person.h>
#include <Farm.h>

TEST(Person, Claim)
{
	UpdateContext uc(10);
	Settlement settlement;
    settlement.AddPerson(std::make_shared<Person>(30000, 1));
    FarmSP building = std::make_shared<Farm>(1000000000);
    settlement.AddBuilding(building);
    settlement.Update(uc);
	EXPECT_TRUE(building->GetOwner());
}
