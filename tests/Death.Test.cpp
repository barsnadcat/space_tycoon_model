#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Object.h>
#include <Space.h>
#include <Entity.h>
#include <Person.h>
#include <Settlement.h>

TEST_F(UpdateContextTestFixture, Death)
{
	auto settlement = ConstructSettlement();
	settlement->space->AddPerson(ConstructPerson(0, 0, {}));
	EXPECT_FALSE(settlement->space->GetPeople().empty());
	settlement->Update(uc);
	EXPECT_TRUE(settlement->space->GetPeople().empty());
}
