#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Person.h>
#include <Settlement.h>
#include <Property.h>
#include <Farm.h>
#include <Entity.h>
#include <Space.h>
#include <Food.h>
#include <Owner.h>

TEST_F(UpdateContextTestFixture, ScavengeFood)
{
	auto settlement = ConstructSettlement();
	auto person1 = ConstructPerson(3000, 0, {});
	auto person2 = ConstructPerson(3000, 0, {});
	auto food1 = ConstructFood(100);
	auto food2 = ConstructFood(100);
	person1->mOwner->ClaimFood(food1);
	EXPECT_EQ(food1->mProperty->GetOwner(), person1);

	settlement->mSpace->AddFood(food1);
	settlement->mSpace->AddFood(food2);
	person2->mPerson->Produce(uc, settlement->mSpace.get(), kScavengeId);
	EXPECT_EQ(food1->mProperty->GetOwner(), person1);
	EXPECT_EQ(food2->mProperty->GetOwner(), person2);
}
