#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>


TEST_F(UpdateContextTestFixture, HungerDamageSlow)
{
    // Huger person looses health
	OwnerPtr person = std::unique_ptr<Person>(new Person(100, 0, {}));
	for (int32_t i = 0; i < 10; ++i)
	{
		person->Update(uc);
	}
	EXPECT_EQ(person->GetHealth(), 80u);
}

TEST_F(UpdateContextTestFixture, Eating)
{
    // Each date person eats one food
	OwnerPtr person = std::unique_ptr<Person>(new Person(100, 0, {}));
	person->Add(kFoodId, std::make_unique<Food>(100));
	person->Add(kFoodId, std::make_unique<Food>(100));
	person->Add(kFoodId, std::make_unique<Food>(100));
	person->Update(uc);
	person->Update(uc);
	person->Update(uc);
	EXPECT_EQ(person->GetHealth(), 97u);
}

TEST_F(UpdateContextTestFixture, EatingMixed)
{
    // Each date person eats one food
	OwnerPtr person = std::unique_ptr<Person>(new Person(100, 0, {}));
	person->Update(uc);
	person->Update(uc);
	person->Add(kFoodId, std::make_unique<Food>(100));
	person->Update(uc);
	EXPECT_EQ(person->GetHealth(), 95u);
}
