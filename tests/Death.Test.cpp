#include <gtest/gtest.h>
#include <easylogging++.h>

#include "Settlement.h"
#include "Update.h"


TEST(Container, Death) 
{
	Settlement settlement;
	settlement.AddPerson(std::make_shared<Person>(0, 0));
	EXPECT_TRUE(settlement.GetEntityIterator()->HasNext());
	Update(settlement.GetEntityIterator());
	EXPECT_FALSE(settlement.GetEntityIterator()->HasNext());
}

