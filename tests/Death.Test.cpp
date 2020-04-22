#include <gtest/gtest.h>
#include <easylogging++.h>

#include "Settlement.h"
#include "Update.h"


TEST(Container, PersonDeath) 
{
	Settlement settlement;
	settlement.AddPerson(std::make_shared<Person>(0, 0));
	EXPECT_TRUE(settlement.GetSpaceIterator().HasNext());
	Update(settlement.GetSpaceIterator());
	EXPECT_FALSE(settlement.GetSpaceIterator().HasNext());
}

