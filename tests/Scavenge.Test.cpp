#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Person.h>
#include <Settlement.h>
#include <Farm.h>

TEST_F(UpdateContextTestFixture, ScavengeFood)
{
	auto settlement = ConstructSettelment();
	auto person1 = ConstructPerson(3000, 0, {});
	auto person2 = ConstructPerson(3000, 0, {});
	auto food1 = std::make_shared<Food>(100);
	auto food2 = std::make_shared<Food>(100);
	person1->mOwner->ClaimFood(food1);
	EXPECT_EQ(food1->mProperty->GetOwner(), person1.get());

	settlement->mSpace->AddFood(food1);
	settlement->mSpace->AddFood(food2);
	person2->Produce(uc, settlement->mSpace.get(), kScavengeId);
	EXPECT_EQ(food1->mProperty->GetOwner(), person1.get());
	EXPECT_EQ(food2->mProperty->GetOwner(), person2.get());
}
