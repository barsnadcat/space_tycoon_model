#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Person.h>

TEST(Hunger, HungerDamageSlow)
{
	// Huger person looses health
	Person person(100, 0);
	for (int i = 0; i < 10; ++i)
	{
		person.Update();
	}
	EXPECT_EQ(person.GetHealth(), 80);
}

TEST(Hunger, Eating)
{
	// Each date person eats one food
	Person person(100, 0);
	person.AddFood(std::make_unique<Food>(100));
	person.AddFood(std::make_unique<Food>(100));
	person.AddFood(std::make_unique<Food>(100));
	person.Update();
	person.Update();
	person.Update();
	EXPECT_EQ(person.GetHealth(), 97);
}

TEST(Hunger, EatingMixed)
{
	// Each date person eats one food
	Person person(100, 0);
	person.Update();
	person.Update();
	person.AddFood(std::make_unique<Food>(100));
	person.Update();
	EXPECT_EQ(person.GetHealth(), 95);
}
