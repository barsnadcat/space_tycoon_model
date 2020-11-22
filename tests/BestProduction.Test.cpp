#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Person.h>


TEST(Person, NoProductionIfNoResources)
{
    auto person = std::shared_ptr<Person>(new Person(3000, 0, {}));
}

TEST(Person, NoProductionIfNoTools)
{
}

TEST(Person, NoProductionIfHasEnough)
{
}

TEST(Person, NoProductionIfDoesNotLikeOutput)
{
}

TEST(Person, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
}