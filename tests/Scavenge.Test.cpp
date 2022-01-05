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
	Person* p1 = new Person(&l, 3000, 0, {});
	Food* f1 = new Food(&l, 100);
	p1->AddFood(f1);

	Person* p2 = new Person(&l, 3000, 0, {});
	Food* f2 = new Food(&l, 100);

	p2->Produce(uc, kScavengeId);
	EXPECT_EQ(f1->GetPerson(), p1);
	EXPECT_EQ(f2->GetPerson(), p2);
}

TEST_F(UpdateContextTestFixture, ScavengeFarm)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	Person* p = new Person(&l, 3000, 0, {});
	Farm* b = new Farm(&l, 3000);

	p->Produce(uc, kScavengeId);

	EXPECT_EQ(b->GetPerson(), p);
	EXPECT_EQ(p->GetFarm(), b);
}

TEST_F(UpdateContextTestFixture, ScavengeMove)
{
	Settlement s(2);
	Land& l = s.GetLand(0);

	Person* p = new Person(&l, 3000, 0, {});
	Farm* b = new Farm(&l, 2000);
	p->AddFarm(b);

	Land& l2 = s.GetLand(1);
	Food* f = new Food(&l2, 100);

	p->Produce(uc, kScavengeId);

	EXPECT_EQ(b->GetPerson(), nullptr);
	EXPECT_EQ(f->GetPerson(), p);
	EXPECT_FALSE(p->GetFoods().empty());
	EXPECT_TRUE(p->GetFarm() == nullptr);

	EXPECT_EQ(p->GetLand(), &l2);
	EXPECT_TRUE(l.GetPeople().empty());
	EXPECT_EQ(l2.GetPeople().size(), 1ul);
}
