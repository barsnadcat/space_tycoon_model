#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Space.h>
#include <Owner.h>
#include <Farm.h>
#include <Person.h>
#include <Settlement.h>

TEST_F(UpdateContextTestFixture, HungerDamageSlow)
{
    // Huger person looses health
	auto person = ConstructPerson(100, 0, {});
	for (int32_t i = 0; i < 10; ++i)
	{
		person->Update(uc);
	}
	EXPECT_EQ(person->mEntity->GetHealth(), 80u);
}

TEST_F(UpdateContextTestFixture, Eating)
{
    // Each date person eats one food
	auto person = ConstructPerson(100, 0, {});
	auto food1 = ConstructFood(100);
	auto food2 = ConstructFood(100);
	auto food3 = ConstructFood(100);
	person->mOwner->ClaimFood(food1);
	person->mOwner->ClaimFood(food2);
	person->mOwner->ClaimFood(food3);
	person->Update(uc);
	person->Update(uc);
	person->Update(uc);
	EXPECT_EQ(person->mEntity->GetHealth(), 97u);
}

TEST_F(UpdateContextTestFixture, EatingMixed)
{
    // Each date person eats one food
	auto person = ConstructPerson(100, 0, {});
	person->Update(uc);
	person->Update(uc);
	auto food1 = ConstructFood(100);
	person->mOwner->ClaimFood(food1);
	person->Update(uc);
	EXPECT_EQ(person->mEntity->GetHealth(), 95u);
}
