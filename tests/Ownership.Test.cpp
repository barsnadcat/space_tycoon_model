#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Person.h>
#include <Building.h>

TEST(Person, Claim)
{
	UpdateContext uc(10);
	Settlement settlement;
    settlement.AddPerson(std::make_shared<Person>(30000, 1));
    settlement.AddBuilding(std::make_shared<Building>(1000000000));
    settlement.Update(uc);
	//EXPECT_TRUE(settlement.GetBuildings().begin()->GetOwner());
}
