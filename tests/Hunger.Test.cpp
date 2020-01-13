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

