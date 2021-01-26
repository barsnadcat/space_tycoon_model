#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>

TEST_F(UpdateContextTestFixture, Birth)
{
	Settlement settlement;
	EXPECT_TRUE(settlement.GetPeople().empty());
	auto person = std::shared_ptr<Person>(new Person(30000, 200, {}));
	person->Produce(uc, &settlement, kReproductionId);
	EXPECT_FALSE(settlement.GetPeople().empty());
}
