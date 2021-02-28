#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Object.h>
#include <Space.h>
#include <Entity.h>
#include <Property.h>
#include <Owner.h>
#include <Person.h>
#include <Settlement.h>

TEST_F(UpdateContextTestFixture, Birth)
{
	auto settlement = ConstructSettlement();
	EXPECT_TRUE(settlement->mSpace->GetPeople().empty());
	auto person = ConstructPerson(30000, 200, {});
	person->Produce(uc, settlement->mSpace.get(), kReproductionId);
	EXPECT_FALSE(settlement->mSpace->GetPeople().empty());
}
