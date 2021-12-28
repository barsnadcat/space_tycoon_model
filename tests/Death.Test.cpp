#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>
#include <Land.h>

TEST_F(UpdateContextTestFixture, Death)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	new Person(&l, 0, 0, {});
	EXPECT_TRUE(l.GetPeople().size() == 1);
	s.Update(uc);
	EXPECT_TRUE(l.GetPeople().size() == 0);
}
