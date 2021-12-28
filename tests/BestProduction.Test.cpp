#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>
#include <Land.h>
#include <Farm.h>
#include <Food.h>

TEST_F(UpdateContextTestFixture, NoProductionIfNoResources)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	auto p = new Person(&l, 3000, 0, {});
	EXPECT_EQ(p->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	auto p = new Person(&l, 3000, 80, {});
	auto b = new Farm(&l, 10000);
	p->AddFarm(b);

	for (int i = 0; i < 20; i++)
	{
		auto f = new Food(&l, 500);
		p->AddFood(f);
	}

	EXPECT_EQ(p->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	auto p = new Person(&l, 3000, 80, {
		{ kFarmId, 0.01f }, { kFoodId, 0.01f }
	});
	EXPECT_EQ(p->GetBestProduction(uc), kScavengeId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	auto p = new Person(&l, 3000, 80, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
	EXPECT_EQ(p->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
	Settlement s(1);
	Land& l = s.GetLand(0);
	auto p = new Person(&l, 3000, 80, {
		{ kFoodId, 0.1f }, { kRandomProductId, 0.1f }
	});
	auto b = new Farm(&l, 10000);
	p->AddFarm(b);
	EXPECT_EQ(p->GetBestProduction(uc), kFarmFoodId);
}
