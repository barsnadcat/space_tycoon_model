#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Person.h>

TEST_F(UpdateContextTestFixture, NoProductionIfNoResources)
{
    auto person = std::shared_ptr<Person>(new Person(3000, 0, {}));
    EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
}

TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
}

TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
}