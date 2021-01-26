#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Farm.h>
#include <Person.h>


TEST_F(UpdateContextTestFixture, HungerDamageSlow)
{
    // Huger person looses health
	PersonSP person = std::shared_ptr<Person>(new Person(100, 0, {}));
	for (int32_t i = 0; i < 10; ++i)
	{
		person->Update(uc);
	}
	EXPECT_EQ(person->GetHealth(), 80u);
}

TEST_F(UpdateContextTestFixture, Eating)
{
    // Each date person eats one food
	PersonSP person = std::shared_ptr<Person>(new Person(100, 0, {}));
	auto food1 = std::make_shared<Food>(100);
	auto food2 = std::make_shared<Food>(100);
	auto food3 = std::make_shared<Food>(100);
	person->ClaimFood(food1);
	person->ClaimFood(food2);
	person->ClaimFood(food3);
	person->Update(uc);
	person->Update(uc);
	person->Update(uc);
	EXPECT_EQ(person->GetHealth(), 97u);
}

TEST_F(UpdateContextTestFixture, EatingMixed)
{
    // Each date person eats one food
	PersonSP person = std::shared_ptr<Person>(new Person(100, 0, {}));
	person->Update(uc);
	person->Update(uc);
	auto food1 = std::make_shared<Food>(100);
	person->ClaimFood(food1);
	person->Update(uc);
	EXPECT_EQ(person->GetHealth(), 95u);
}
