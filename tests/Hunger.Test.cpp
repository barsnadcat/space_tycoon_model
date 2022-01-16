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
	Person* p = new Person(&l, 100, 0, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
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
	Person* p = new Person(&l, 100, 0, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
	for (auto i = 0; i < 3; i++)
	{
		Food* f = new Food(&l, 100);
		p->AddFood(f);
	}
	EXPECT_EQ(p->GetPersonOwned(kFoodId), 3);
	s.Update(uc);
	EXPECT_EQ(p->GetPersonOwned(kFoodId), 2);
	s.Update(uc);
	EXPECT_EQ(p->GetPersonOwned(kFoodId), 1);
	s.Update(uc);
	EXPECT_EQ(p->GetPersonOwned(kFoodId), 0);
	EXPECT_EQ(p->GetHealth(), 97u);
}

TEST_F(UpdateContextTestFixture, EatingMixed)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
    // Each date person eats one food
	Person* p = new Person(&l, 100, 0, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
	s.Update(uc);
	s.Update(uc);
	Food* f = new Food(&l, 100);
	p->AddFood(f);
	s.Update(uc);
	EXPECT_EQ(p->GetHealth(), 95u);
}
