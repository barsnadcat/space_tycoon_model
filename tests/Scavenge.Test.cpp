#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Farm.h>
#include <Land.h>
#include <Person.h>
#include <Food.h>

TEST_F(UpdateContextTestFixture, ScavengeFood)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	Person* p1 = new Person(&s, 3000, 0, {});
	l.AddPerson(p1);
	Food* f1 = new Food(&s, 100);
	p1->AddFood(f1);
	l.AddFood(f1);

	Person* p2 = new Person(&s, 3000, 0, {});
	l.AddPerson(p2);
	Food* f2 = new Food(&s, 100);
	l.AddFood(f2);

	p2->Produce(uc, kScavengeId);
	EXPECT_EQ(f1->GetPerson(), p1);
	EXPECT_EQ(f2->GetPerson(), p2);
}
