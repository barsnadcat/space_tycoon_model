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

TEST(Hunger, Eating)
{
	//Each date person eats one food
	Person person(100, 0);
	person.AddFood(std::make_shared<Food>(100));
	person.Update(1);
	EXPECT_EQ(person.GetHealth(), 99);
}
