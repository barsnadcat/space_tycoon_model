#include <easylogging++.h>
#include <gtest/gtest.h>

#include <Person.h>
#include <UpdateContext.h>
#include <ObjectiveUtilitiesConfig.h>
#include <ProductionsConfig.h>

TEST(Person, NoProductionIfNoResources)
{
    UpdateContext uc;
    uc.mObjectiveUtilities = GetObjectiveUtilities();
    uc.mProductions = GetProductions();
    auto person = std::shared_ptr<Person>(new Person(3000, 0, {}));
    EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
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