#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Person.h>
#include <Food.h>

TEST_F(UpdateContextTestFixture, ScavengeFood)
{
	Settlement settlement(1);

	Person* person1 = new Person(3000, 0, {});
	Food* food1 = new Food(100);
	person1->Add(kFoodId, std::unique_ptr<Item>(food1));
	settlement.GetLand(0)->GetNullBuilding().AddOwner(std::unique_ptr<Person>(person1));

	Person* person2 = new Person(3000, 0, {});
	settlement.GetLand(0)->GetNullBuilding().AddOwner(std::unique_ptr<Person>(person2));
	Food* food2 = new Food(100);
	settlement.GetLand(0)->GetNullBuilding().GetNullOwner().Add(kFoodId, std::unique_ptr<Item>(food2));

	person2->Produce(uc, kScavengeId);
	EXPECT_EQ(food1->GetOwner(), person1);
	EXPECT_EQ(food2->GetOwner(), person2);
}
