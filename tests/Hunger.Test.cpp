#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Building.h>
#include <Person.h>
#include <UpdateContext.h>


TEST(Person, HungerDamageSlow)
{
    // Huger person looses health
	UpdateContext uc;
	Person person(100, 0);
	for (int i = 0; i < 10; ++i)
	{
		person.Update(uc);
	}
	EXPECT_EQ(person.GetHealth(), 80);
}

TEST(Person, Eating)
{
    // Each date person eats one food
	UpdateContext uc;
	Person person(100, 0);
	person.AddFood(std::make_unique<Food>(100));
	person.AddFood(std::make_unique<Food>(100));
	person.AddFood(std::make_unique<Food>(100));
	person.Update(uc);
	person.Update(uc);
	person.Update(uc);
	EXPECT_EQ(person.GetHealth(), 97);
}

TEST(Person, EatingMixed)
{
    // Each date person eats one food
	UpdateContext uc;
	Person person(100, 0);
	person.Update(uc);
	person.Update(uc);
	person.AddFood(std::make_unique<Food>(100));
	person.Update(uc);
	EXPECT_EQ(person.GetHealth(), 95);
}
