#include <easylogging++.h>
#include <gtest/gtest.h>

#include "Settlement.h"

TEST(Container, PersonPickup)
{
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(5, 1));
	settlement.Update();
	settlement.Update();
	settlement.Update();
	settlement.Update();
	EXPECT_FALSE(settlement.GetPeople().empty());
}
