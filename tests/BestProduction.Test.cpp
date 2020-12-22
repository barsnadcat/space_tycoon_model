#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>
#include <Farm.h>

TEST_F(UpdateContextTestFixture, NoProductionIfNoResources)
{
    auto person = std::shared_ptr<Person>(new Person(3000, 0, {}));
    EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfHasEnough)
{
    auto settlement = std::shared_ptr<Settlement>(new Settlement());
    auto person = std::shared_ptr<Person>(new Person(3000, 80, {}));
    settlement->AddPerson(person);
    auto farm = std::shared_ptr<Farm>(new Farm(10000));
    settlement->AddBuilding(farm);
    person->ClaimFarm(farm);
    for (int i = 0; i < 20; i++)
    {
        auto food = std::shared_ptr<Food>(new Food(500));
        settlement->AddFood(food);
        person->ClaimFood(food);
    }
    
    EXPECT_EQ(person->GetBestProduction(uc), kInvalidId);
}

TEST_F(UpdateContextTestFixture, NoProductionIfNoTools)
{
}


TEST_F(UpdateContextTestFixture, NoProductionIfDoesNotLikeOutput)
{
}

TEST_F(UpdateContextTestFixture, ProductionIfDoesNotLikeOutputButHasNotEnough)
{
}