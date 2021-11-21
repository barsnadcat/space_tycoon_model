#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Land.h>
#include <Person.h>
#include <Food.h>


TEST_F(UpdateContextTestFixture, HungerDamageSlow)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
    // Huger person looses health
	Person* p = new Person(&s, 100, 0, {});
	l.AddPerson(p);
	for (int32_t i = 0; i < 10; ++i)
	{
		s.Update(uc);
	}
	EXPECT_EQ(p->GetHealth(), 80u);
}

TEST_F(UpdateContextTestFixture, Eating)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
    // Each date person eats one food
	Person* p = new Person(&s, 100, 0, {});
	for (auto i = 0; i < 3; i++)
	{
		Food* f = new Food(&s, 100);
		p->AddFood(f);
		l.AddFood(f);
	}
	EXPECT_EQ(p->GetPersonOwned(kFoodId), 3);
	s.Update(uc);
	EXPECT_EQ(l.GetFoods().size(), 2ul);
	s.Update(uc);
	EXPECT_EQ(l.GetFoods().size(), 1ul);
	s.Update(uc);
	EXPECT_TRUE(l.GetFoods().empty());
	EXPECT_EQ(p->GetHealth(), 97u);
}

TEST_F(UpdateContextTestFixture, EatingMixed)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
    // Each date person eats one food
	Person* p = new Person(&s, 100, 0, {});
	s.Update(uc);
	s.Update(uc);
	Food* f = new Food(&s, 100);
	p->AddFood(f);
	l.AddFood(f);
	s.Update(uc);
	EXPECT_EQ(p->GetHealth(), 95u);
}
