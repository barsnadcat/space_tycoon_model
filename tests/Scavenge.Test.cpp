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

TEST_F(UpdateContextTestFixture, ScavengeFarm)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	Person* p = new Person(&s, 3000, 0, {});
	l.AddPerson(p);

	Farm* b = new Farm(&s, 3000);
	l.AddFarm(b);

	p->Produce(uc, kScavengeId);

	EXPECT_EQ(b->GetPerson(), p);
	EXPECT_EQ(p->GetFarms().size(), 1ul);
	EXPECT_EQ(p->GetFarms().at(0), b);
}

TEST_F(UpdateContextTestFixture, ScavengeMove)
{
	Settlement s(2);
	Land& l = s.GetLand(0);

	Person* p = new Person(&s, 3000, 0, {});
	l.AddPerson(p);

	Food* f = new Food(&s, 100);
	l.AddFood(f);
	p->AddFood(f);

	Land& l2 = s.GetLand(1);
	Farm* b = new Farm(&s, 2000);
	l2.AddFarm(b);

	p->Produce(uc, kScavengeId);

	EXPECT_EQ(b->GetPerson(), p);
	EXPECT_EQ(f->GetPerson(), nullptr);
	EXPECT_TRUE(p->GetFoods().empty());
	EXPECT_EQ(p->GetFarms().size(), 1ul);

	EXPECT_EQ(p->GetLand(), &l2);
	EXPECT_TRUE(l.GetPeople().empty());
	EXPECT_EQ(l.GetFoods().size(), 1ul);
	EXPECT_EQ(l2.GetPeople().size(), 1ul);
	EXPECT_TRUE(l2.GetFoods().empty());
}
