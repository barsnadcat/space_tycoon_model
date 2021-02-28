#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Space.h>
#include <Entity.h>
#include <Owner.h>
#include <Person.h>
#include <Farm.h>
#include <Food.h>

TEST_F(UpdateContextTestFixture, NoProductionIfNoResources)
{
	auto person = ConstructPerson(3000, 0, {});
	EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
	auto settlement = ConstructSettlement();
	auto person = ConstructPerson(3000, 80, {});
	settlement->mSpace->AddPerson(person);
	auto farm = ConstructFarm(10000);
	settlement->mSpace->AddBuilding(farm);
	person->mOwner->ClaimFarm(farm);
	for (int i = 0; i < 20; i++)
	{
		auto food = ConstructFood(500);
		settlement->mSpace->AddFood(food);
		person->mOwner->ClaimFood(food);
	}

	EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFarmId, 0.01f }, { kFoodId, 0.01f }
	});
	EXPECT_EQ(person->GetBestProduction(uc), kScavengeId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
	EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFoodId, 0.1f }, { kRandomProductId, 0.1f }
	});
	auto farm = ConstructFarm(10000);
	person->mOwner->ClaimFarm(farm);
	EXPECT_EQ(person->GetBestProduction(uc), kFarmFoodId);
}
