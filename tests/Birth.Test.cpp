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
	EXPECT_TRUE(settlement->space->GetPeople().empty());
	auto person = ConstructPerson(30000, 200, {});
	person->person->Produce(uc, settlement->space.get(), kReproductionId);
	EXPECT_FALSE(settlement->space->GetPeople().empty());
}
