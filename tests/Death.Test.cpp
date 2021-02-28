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
	settlement->mSpace->AddPerson(ConstructPerson(0, 0, {}));
	EXPECT_FALSE(settlement->mSpace->GetPeople().empty());
	settlement->Update(uc);
	EXPECT_TRUE(settlement->mSpace->GetPeople().empty());
}
