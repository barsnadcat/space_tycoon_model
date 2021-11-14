#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>
#include <Farm.h>

TEST_F(UpdateContextTestFixture, NoProductionIfNoResources)
{
	Settlement settlement(1);
	auto person = new Person(&settlement, 3000, 0, {});
	settlement.GetLand(0).GetNullBuilding().AddOwner(person);	
	EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
	Settlement s(1);
	auto p = new Person(&s, 3000, 80, {});
	s.GetLand(0).GetNullBuilding().AddOwner(p);
	auto b = new Farm(&s, 10000);
	s.GetLand(0).AddBuilding(b);

	p->ClaimFarm(b);
	for (int i = 0; i < 20; i++)
	{
		auto f = new Food(&s, 500);
		p->AddFood(f);
	}

	EXPECT_EQ(p->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
	Settlement s(1);
	auto p = new Person($s, 3000, 80, {{ kFarmId, 0.01f }, { kFoodId, 0.01f }});
	s.GetLand(0).AddOwner(p);
	EXPECT_EQ(person->GetBestProduction(uc), kScavengeId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
	Settlement s(1);
	auto p = new Person(&s, 3000, 80, {{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }});
	s.GetLand(0).AddOwner(p);
	EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}


TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
	Settlement s(1);
	auto p = new Person(&s, 3000, 80, {{ kFoodId, 0.1f }, { kRandomProductId, 0.1f }});
	auto b = new Farm(&s, 10000);
	s.GetLand(0).AddBuilding(b);
	b->AddOwner(p);
	p->ClaimFarm(b);
	EXPECT_EQ(person->GetBestProduction(uc), kFarmFoodId);
}

