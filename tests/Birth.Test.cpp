#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Person.h>
#include <Settlement.h>
#include <Land.h>

TEST_F(UpdateContextTestFixture, Birth)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	EXPECT_TRUE(l.GetPeople().empty());
	Person* p = new Person(&l, 30000, 200, {});
	EXPECT_EQ(l.GetPeople().size(), 1ul);
	p->Produce(uc, kReproductionId);
	EXPECT_EQ(l.GetPeople().size(), 2ul);
}
