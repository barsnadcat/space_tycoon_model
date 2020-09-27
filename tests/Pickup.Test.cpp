#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Settlement.h>
#include <UpdateContext.h>
#include <Building.h>

TEST(Person, Pickup)
{
	UpdateContext uc(10);
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(5, 1));
	settlement.Update(uc);
	settlement.Update(uc);
	settlement.Update(uc);
	settlement.Update(uc);
	EXPECT_FALSE(settlement.GetPeople().empty());
}
