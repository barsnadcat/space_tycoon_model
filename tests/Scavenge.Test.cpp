#include <easylogging++.h>
#include <UpdateContextTestFixture.h>

#include <Settlement.h>
#include <Land.h>
#include <Person.h>
#include <Food.h>

TEST_F(UpdateContextTestFixture, ScavengeFood)
{
	Settlement settlement(1);
	Person* person1 = new Person(&settlement, 3000, 0, {});
	settlement.GetLand(0).GetNullBuilding().AddOwner(person1);
	Food* food1 = new Food(&settlement, 100);
	person1->AddFood(food1);

	Person* person2 = new Person(&settlement, 3000, 0, {});
	settlement.GetLand(0).GetNullBuilding().AddOwner(person2);
	Food* food2 = new Food(&settlement, 100);
	settlement.GetLand(0).GetNullBuilding().GetNullOwner().AddFood(food2);

	person2->Produce(uc, kScavengeId);
	EXPECT_EQ(food1->GetOwner(), person1);
	EXPECT_EQ(food2->GetOwner(), person2);
}
