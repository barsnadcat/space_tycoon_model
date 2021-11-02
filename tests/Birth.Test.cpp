#include <src/easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Building.h>
#include <Person.h>

TEST_F(UpdateContextTestFixture, Birth)
{
	Building building(1, 0);
	EXPECT_TRUE(building.GetOwners().empty());
	Person* person = new Person(30000, 200, {});
	building.AddOwner(std::unique_ptr<Person>(person));
	person->Produce(uc, kReproductionId);
	EXPECT_EQ(building.GetOwners().size() == 2);
}
