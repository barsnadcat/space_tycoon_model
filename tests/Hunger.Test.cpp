#include <gtest/gtest.h>
#include <easylogging++.h>

#include <Person.h>


TEST(Hunger, HungerDamage) 
{
	//Huger person looses health
	Person person(100, 0);
	person.Update(10);
	EXPECT_EQ(person.GetHealth(), 80);
}

TEST(Hunger, HungerDamageSlow) 
{
	//Huger person looses health
	Person person(100, 0);
	for (int i = 0; i < 10; ++i)
	{
		person.Update(1);
	}
	EXPECT_EQ(person.GetHealth(), 80);
}


TEST(Hunger, Eating)
{
	//Each date person eats one food
	Person person(100, 0);
	person.AddFood(std::make_shared<Food>(100));
	person.AddFood(std::make_shared<Food>(100));
	person.AddFood(std::make_shared<Food>(100));
	person.Update(1);
	person.Update(1);
	person.Update(1);
	EXPECT_EQ(person.GetHealth(), 97);
}

TEST(Hunger, EatingSlow)
{
	//Each date person eats one food
	Person person(100, 0);
	person.AddFood(std::make_shared<Food>(100));
	person.AddFood(std::make_shared<Food>(100));
	person.AddFood(std::make_shared<Food>(100));
	person.Update(3);
	EXPECT_EQ(person.GetHealth(), 97);
}

TEST(Hunger, EatingMixed)
{
	//Each date person eats one food
	Person person(100, 0);
	person.Update(1);
	person.Update(1);
	person.AddFood(std::make_shared<Food>(100));
	person.Update(1);
	EXPECT_EQ(person.GetHealth(), 96);
}
