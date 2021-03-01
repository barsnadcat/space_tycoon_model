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
	EXPECT_EQ(person->person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
	auto settlement = ConstructSettlement();
	auto person = ConstructPerson(3000, 80, {});
	settlement->space->Add(kFamilyMemberId, person);
	auto farm = ConstructFarm(10000);
	settlement->space->Add(kFarmId, farm);
	person->owner->Claim(kFarmId, farm);
	for (int i = 0; i < 20; i++)
	{
		auto food = ConstructFood(500);
		settlement->space->Add(kFoodId, food);
		person->owner->Claim(kFoodId, food);
	}

	EXPECT_EQ(person->person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFarmId, 0.01f }, { kFoodId, 0.01f }
	});
	EXPECT_EQ(person->person->GetBestProduction(uc), kScavengeId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFarmId, 0.01f }, { kRandomProductId, 0.01f }
	});
	EXPECT_EQ(person->person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
	auto person = ConstructPerson(3000, 80, {
		{ kFoodId, 0.1f }, { kRandomProductId, 0.1f }
	});
	auto farm = ConstructFarm(10000);
	person->owner->Claim(kFarmId, farm);
	EXPECT_EQ(person->person->GetBestProduction(uc), kFarmFoodId);
}
