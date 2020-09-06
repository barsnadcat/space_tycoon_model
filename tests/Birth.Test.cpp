#include <easylogging++.h>
#include <gtest/gtest.h>

#include "Settlement.h"
#include "UpdateContext.h"

TEST(Person, Birth)
{
	UpdateContext uc(4);
	Settlement settlement;
	settlement.AddPerson(std::make_unique<Person>(30000, 200));
	settlement.Update(uc);
	EXPECT_EQ(settlement.GetPeople().size(), 2);
}
