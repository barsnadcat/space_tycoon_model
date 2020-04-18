#include <gtest/gtest.h>
#include <easylogging++.h>

#include "Settlement.h"
#include "Death.h"


TEST(Container, Death) 
{
	Settlement settlement;
	settlement.AddPerson(std::make_shared<Person>(0, 0));
	EXPECT_TRUE(settlement.GetEntityIterator()->HasNext());
	Death(settlement.GetEntityIterator());
	EXPECT_FALSE(settlement.GetEntityIterator()->HasNext());
}

